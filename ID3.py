#! /usr/bin/env python

import os
import sys
import binascii
tag = False
tagPlus = False

def openMP3( fileName ): #fileName needs to be in quotes if run in lynix 
    try:
        mp3 = open( fileName, "rb", 0 )
        return mp3, True
    except IOError:
        print("File name was invalid")
        return "null", False

def headerFunc( dataread ):
    found = False
    name = ""
    if ( dataread == b'AENC'):
        found = True
        name = "Audio encryption"
    elif ( dataread == b'APIC'):
        found = True
        name = "Attached picture"
    elif ( dataread == b'COMM'):
        found = True
        name = "Comments"
    elif ( dataread == b'COMR'):
        found = True
        name = "Commercial frame"
    elif ( dataread == b'ENCR'):
        found = True
        name = "Encryption method registration"
    elif ( dataread == b'EQUA'):
        found = True
        name = "Equalization"
    elif ( dataread == b'ETCO'):
        found = True
        name = "Event timing codes"
    elif ( dataread == b'GEOB'):
        found = True
        name = "General encapsulated object"
    elif ( dataread == b'GRID'):
        found = True
        name = "Group identification registration"
    elif ( dataread == b'IPLS'):
        found = True
        name = "Involved people list"
    elif ( dataread == b'LINK'):
        found = True
        name = "Linked information"
    elif ( dataread == b'MCDI'):
        found = True
        name = "Music CD identifier"
    elif ( dataread == b'MLLT'):
        found = True
        name = "MPEG location lookup table"
    elif ( dataread == b'OWNE'):
        found = True
        name = "Ownership frame"
    elif ( dataread == b'PRIV'):
        found = True
        name = "Private frame"
    elif ( dataread == b'PCNT'):
        found = True
        name = "Play counter"
    elif ( dataread == b'POSS'):
        found = True
        name = "Popularimeter"
    elif ( dataread == b'RBUF'):
        found = True
        name = "Position synchronisation frame"
    elif ( dataread == b'RVAD'):
        found = True
        name = "Recommended buffer size"
    elif ( dataread == b'RVRB'):
        found = True
        name = "Reverb"
    elif ( dataread == b'SYLT'):
        found = True
        name = "Synchronized lyric/text"
    elif ( dataread == b'SYTC'):
        found = True
        name = "Synchronized tempo codes"
    elif ( dataread == b'TALB'):
        found = True
        name = "Album/Movie/Show title"
    elif ( dataread == b'TBPM'):
        found = True
        name = "BPM (beats per minute)"
    elif ( dataread == b'TCOM'):
        found = True
        name = "Composer"
    elif ( dataread == b'TCON'):
        found = True
        name = "Content type"
    elif ( dataread == b'TCOP'):
        found = True
        name = "Copyright message"
    elif ( dataread == b'TDAT'):
        found = True
        name = "Date"
    elif ( dataread == b'TDLY'):
        found = True
        name = "Playlist delay"
    elif ( dataread == b'TENC'):
        found = True
        name = "Encoded by"
    elif ( dataread == b'TEXT'):
        found = True
        name = "Lyricist/Text writer"
    elif ( dataread == b'TFLT'):
        found = True
        name = "File type"
    elif ( dataread == b'TIME'):
        found = True
        name = "Time"
    elif ( dataread == b'TIT1'):
        found = True
        name = "Content group description"
    elif ( dataread == b'TIT2'):
        found = True
        name = "Title/songname/content description"
    elif ( dataread == b'TIT3'):
        found = True
        name = "Subtitle/Description refinement"
    elif ( dataread == b'TKEY'):
        found = True
        name = "Initial key"
    elif ( dataread == b'TLAN'):
        found = True
        name = "Language(s)"
    elif ( dataread == b'TLEN'):
        found = True
        name = "Length"
    elif ( dataread == b'TMED'):
        found = True
        name = "Media type"
    elif ( dataread == b'TOAL'):
        found = True
        name = "Original album/movie/show title"
    elif ( dataread == b'TOFN'):
        found = True
        name = "Original filename"
    elif ( dataread == b'TOLY'):
        found = True
        name = "Original lyricist(s)/text writer(s)"
    elif ( dataread == b'TOPE'):
        found = True
        name = "Original artist(s)/performer(s)"
    elif ( dataread == b'TORY'):
        found = True
        name = "Original release year"
    elif ( dataread == b'TOWN'):
        found = True
        name = "File owner/licensee"
    elif ( dataread == b'TPE1'):
        found = True
        name = "Lead performer(s)/Soloist(s)"
    elif ( dataread == b'TPE2'):
        found = True
        name = "Band/orchestra/accompaniment"
    elif ( dataread == b'TPE3'):
        found = True
        name = "Conductor/performer refinement"
    elif ( dataread == b'TPE4'):
        found = True
        name = "Interpreted, remixed, or otherwise modified by"
    elif ( dataread == b'TPOS'):
        found = True
        name = "Part of a set"
    elif ( dataread == b'TPUB'):
        found = True
        name = "Publisher"
    elif ( dataread == b'TRCK'):
        found = True
        name = "Track number/Position in set"
    elif ( dataread == b'TRDA'):
        found = True
        name = "Recording dates"
    elif ( dataread == b'TRSN'):
        found = True
        name = "Internet radio station name"
    elif ( dataread == b'TRSO'):
         found = True
         name = "Internet radio station owner"
    elif ( dataread == b'TSIZ'):
        name = "Size"
        found = True
    elif ( dataread == b'TSRC'):
        name = "ISRC (international standard recording code)"
        found = True
    elif ( dataread == b'TSSE'):
        name = "Software/Hardware and settings used for encoding"
        found = True
    elif ( dataread == b'TYER'):
        name = "Year"
        found = True
    elif ( dataread == b'TXXX'):
        name = "User defined text information frame"
        found = True
    elif ( dataread == b'UFID'):
        name = "Unique file identifier"
        found = True
    elif ( dataread == b'USER'):
        name = "Terms of use"
        found = True
    elif ( dataread == b'USLT'):
        found = True
        name = "Unsychronized lyric/text transcription"
    elif ( dataread == b'WCOM'):
        name = "Commercial information"
        found = True
    elif ( dataread == b'WCOP'):
        name = "Copyright/Legal information"
        found = True
    elif ( dataread == b'WOAF'):
        name = "Official audio file webpage"
        found = True
    elif ( dataread == b'WOAR'):
        name = "Official artist/performer webpage"
        found = True
    elif ( dataread == b'WOAS'):
        name = "Official audio source webpage"
        found = True
    elif ( dataread == b'WORS'):
        name = "Official internet radio station homepage"
        found = True
    elif ( dataread == b'WPAY'):
        name = "Payment"
        found = True
    elif ( dataread == b'WPUB'):
        found = True
        name = "Publishers official webpage"
    elif ( dataread == b'WXXX'):
        found = True
        name = "User defined URL link frame"
    return found, name


def genreDecode( genre ):
    if( genre == 0 ):
        genre = "Blues"
    elif( genre == 1 ):
        genre = "Classic Rock"
    elif( genre == 2 ):
        genre = "Country"
    elif( genre == 3 ):
        genre = "Dance"
    elif( genre == 4 ):
        genre = "Disco"
    elif( genre == 5 ):
        genre = "Funk"
    elif( genre == 6 ):
        genre = 'Grunge'
    elif( genre == 7 ):
        genre = 'Hip-Hop'
    elif( genre == 8 ):
        genre = 'Jazz'
    elif( genre == 9 ):
        genre = 'Metal'
    elif( genre == 10 ):
        genre = 'New Age'
    elif( genre == 11):
        genre = 'Oldies'
    elif( genre == 12 ):
        genre = 'Other'
    elif( genre == 13 ):
        genre = 'Pop'
    elif( genre == 14 ):
        genre = 'R&B'
    elif( genre == 15 ):
        genre = 'Rap'
    elif( genre == 16 ):
        genre = 'Reggae'
    elif( genre == 17 ):
        genre = 'Rock'
    elif( genre == 18 ):
        genre = 'Techno'
    elif( genre == 19 ):
        genre = 'Industrial'
    elif( genre == 20 ):
        genre = 'Alternative'
    elif( genre == 21 ):
        genre = 'Ska'
    elif( genre == 22 ):
        genre = 'Death Metal'
    elif( genre == 23 ):
        genre = 'Pranks'
    elif( genre == 24 ):
        genre = 'Soundtrack'
    elif( genre == 25 ):
        genre = 'Euro-Techno'
    elif( genre == 26 ):
        genre = 'Ambient'
    elif( genre == 27 ):
        genre = 'Trip-Hop'
    elif( genre == 28 ):
        genre = 'Vocal'
    elif( genre == 29 ):
        genre = 'Jazz+Funk'
    elif( genre == 30 ):
        genre = 'Fusion'
    elif( genre == 31 ):
        genre = 'Trance'
    elif( genre == 32 ):
        genre = 'Classical'
    elif( genre == 33):
        genre = 'Instrumental'
    elif( genre == 34 ):
        genre = 'Acid'
    elif( genre == 35 ):
        genre = 'House'
    elif( genre == 36):
        genre = 'Game'
    elif( genre == 37 ):
        genre = 'Sound Clip'
    elif( genre == 38 ):
        genre = 'Gospel'
    elif( genre == 39):
        genre = 'Noise'
    elif( genre == 40):
        genre = 'AlternRock'
    elif( genre == 41 ):
        genre = 'Bass'
    elif( genre == 42 ):
        genre = 'Soul'
    elif( genre == 43 ):
        genre = 'Punk'
    elif( genre == 44 ):
        genre = 'Space'
    elif( genre == 45 ):
        genre = 'Meditative'
    elif( genre == 46 ):
        genre = 'Instrumental Pop'
    elif( genre == 47 ):
        genre = 'Instrumental Rock'
    elif( genre == 48 ):
        genre = 'Ethnic'
    elif( genre == 49 ):
        genre = 'Gothic'
    elif( genre == 50 ):
        genre = 'Darkwave'
    elif( genre == 51 ):
        genre = 'Techno-Industrial'
    elif( genre == 52 ):
        genre = 'Electronic'
    elif( genre == 53 ):
        genre = 'Pop-Folk'
    elif( genre == 54):
        genre = 'Eurodance'
    elif( genre == 55):
        genre = 'Dream'
    elif( genre == 56):
        genre = 'Southern Rock'
    elif( genre == 57):
        genre = 'Comedy'
    elif( genre == 58):
        genre = 'Cult'
    elif( genre == 59):
        genre = 'Gangsta'
    elif( genre == 60):
        genre = 'Top 40'
    elif( genre == 61 ):
        genre = 'Christian Rap'
    elif( genre == 62):
        genre = 'Pop/Funk'
    elif( genre == 63 ):
        genre = 'Jungle'
    elif( genre == 64 ):
        genre = 'Native American'
    elif( genre == 65):
        genre = 'Cabaret'
    elif( genre == 66):
        genre = 'New Wave'
    elif( genre == 67):
        genre = 'Psychadelic'
    elif( genre == 68):
        genre = 'Rave'
    elif( genre == 69):
        genre = 'Showtunes'
    elif( genre ==  70):
        genre = 'Trailer'
    elif( genre == 71 ):
        genre = 'Lo-Fi'
    elif( genre == 72):
        genre = 'Tribal'
    elif( genre == 73):
        genre = 'Acid Punk'
    elif( genre == 74):
        genre = 'Acid Jazz'
    elif( genre == 75 ):
        genre = 'Polka'
    elif( genre == 76):
        genre = 'Retro'
    elif( genre == 77):
        genre = 'Musical'
    elif( genre == 78):
        genre = 'Rock & Roll'
    elif( genre == 79 ):
        genre = 'Hard Rock'

    return genre


boolRet = False
while(boolRet == False ):
    fileName = input("Select song to evaluate: ")
    mp3, boolRet = openMP3(fileName)

if( boolRet == True ):
    ID3 = mp3.read(3)
    if( ID3 == b'ID3' ):
        version = mp3.read(1)
        versionNum = int( binascii.hexlify(version), 16)
        if( versionNum == 3 or versionNum ==2 or versionNum == 1 ):
            mp3.read(2)
            leng = mp3.read(4)
            length = int( binascii.hexlify( leng ),16 )
            test = mp3.read(4)
            index = 4
            testBool, name = headerFunc(test)
            if( testBool == False ):
                mp3.read(2)
                test = mp3.read(4)
                index += 6
                testBool, name = headerFunc(test)
                if( testBool == False ):
                    mp3.read(2)
                    index += 2
            else:
                    test.strip().replace(b"\x00",b"")
                    test1 = test.decode("utf-8")
                    
                    if( testBool == True ):
                        size = mp3.read(4)
                        sizeInt = int( binascii.hexlify(size), 16)
                        print(sizeInt)
                        mp3.read(2)
                        index += 6
                        frameContent = mp3.read(sizeInt)
                        index += sizeInt
                        frameContent.strip().replace(b"\x00",b"")
                        frameContent = frameContent.decode("utf-8")
                        print(name, ":", frameContent, "\0" )
                        
                        
            counter = 1
            while( index < length ):
                counter +=1    
                test = mp3.read(4)
                index += 4
                test.strip().replace(b"\x00",b"")
                #test1 = test.decode("utf-8")
                boolTest, name = headerFunc(test)
                if( boolTest == True ):
                    size = mp3.read(4)
                    sizeInt = int( binascii.hexlify(size), 16)
                    mp3.read(2)
                    index += 6
                    frameContent = mp3.read(sizeInt)
                    index += sizeInt
                    frameContent.strip().replace(b"\x00",b"")
                    frameContent = frameContent.decode("utf-8")
                    print(name, ":", frameContent, "\0" )
                else:
                    index += 4

            print(" Frames: ", counter)

    mp3.seek(-355,2)
    tagString = mp3.read(4)
    if (tagString == b'TAG+'):
        tagPlus == True
        title = mp3.read(60)
        title.strip().replace(b"\x00", b"")
        title = title.decode("utf-8")
        print( title )
        artist = mp3.read(60)
        artist.strip().replace(b"\x00", b"")
        artist = artist.decode("utf-8")
        print( artist )
        album = mp3.read(60)
        album.strip().replace(b"\x00", b"")
        album = album.decode("utf-8")
        print( ablum )
        speed = mp3.read(1)
        speed.strip().replace(b"\x00", b"")
        speed = speed.decode("utf-8")
        print( speed )
        genre = mp3.read(30)
        genre.strip().replace(b"\x00", b"")
        genre = genre.decode("utf-8")
        print( genre )
        start.strip().replace(b"\x00", b"")
        start = start.decode("utf-8")
        start = mp3.read(6)
        print( start )
        end.strip().replace(b"\x00", b"")
        end = end.decode("utf-8")
        end = mp3.read(6)
        print( end )
    else:
        mp3.read(223)
        tagString = mp3.read(3)
    if (tagString == b'TAG'):
        tag == True
        Current = 2011;
        title = mp3.read(30)
        title.strip().replace(b"\x00", b"")
        title = title.decode("utf-8")
        print( "Title: ", title )
        artist = mp3.read(30)
        artist.strip().replace(b"\x00", b"")
        artist = artist.decode("utf-8")
        print( "Artist: ",artist )
        album = mp3.read(30)
        album.strip().replace(b"\x00", b"")
        album = album.decode("utf-8")
        print( "Album: ",album )
        year = mp3.read(4)
        year.strip().replace(b"\x00", b"")
        year = year.decode("utf-8")
        year1 = int( year )
        Current = Current - year1
        print( "Year: ",year, " (", Current, ")" )
        comment = mp3.read(28)
        comment.strip().replace(b"\x00", b"")
        comment = comment.decode("utf-8")
        zeroByte= ord(mp3.read(1))
        track = ord( mp3.read(1))
        print( "Track: ",track )
        genre = ord(mp3.read(1))
        genre = genreDecode( genre )
        print( "Genre: ", genre)

    mp3.close()

    


