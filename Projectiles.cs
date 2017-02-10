using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

using WheelOfTime.SpriteClasses;
using WheelOfTime.TileEngineM;
using WheelOfTime.GameScreens;
using WheelOfTime;

namespace WheelOfTime.Components
{
    class Projectiles
    {
        int Speed;
        String name;
        Texture2D SpriteSheet, ArrowSheet;
        public AnimatedSprite sprite, ArcheryTarget;
        Vector2 velocity, targetPos, start, PosDiff;
        float distanceX, distanceY;
        public Dictionary<AnimationKey, Animation> animations;
        public Dictionary<AnimationKey, Animation> Explosion_animations;
        public Explosion expl;
        double heading, desiredHeading;
        Game g;
        public bool active = true;

        #region Constructor Region
        // constructor
        public Projectiles(String CharacterName, Texture2D ProjectileTexture, double desiredHeading, Vector2 Target, Vector2 StartPos)
        {
            this.Speed = 6;
            this.name = CharacterName + "_projectile";
            this.heading = desiredHeading;
            this.velocity.X = (float)(1 * Math.Cos(heading));
            this.velocity.Y = (float)(1 * Math.Sin(heading));
            this.targetPos = Target;
            this.animations = new Dictionary<AnimationKey, Animation>();
            this.Explosion_animations = new Dictionary<AnimationKey, Animation>();
            this.start = StartPos;


        }
        public Projectiles( Texture2D ProjectileTexture, double desiredHeading,  Vector2 StartPos, String CharacterName)
        {
            this.Speed = 6;
            this.name = CharacterName + "_projectile";
            this.heading = desiredHeading;
            this.velocity.X = (float)(1 * Math.Cos(heading * Math.PI/ 180 ));
            this.velocity.Y = (float)(1 * Math.Sin(heading *- Math.PI/ 180 ));
            //this.targetPos = Target;
            this.animations = new Dictionary<AnimationKey, Animation>();
            this.Explosion_animations = new Dictionary<AnimationKey, Animation>();
            this.start = StartPos;


        }
        public Projectiles(String CharacterName, Texture2D ProjectileTexture, double desiredHeading, Vector2 Target, Vector2 StartPos, AnimatedSprite ArrowTarget)
        {
             this.Speed = 6;
             this.name = CharacterName + "_projectile";
             this.heading = desiredHeading;
             this.velocity.X = (float)(1 * Math.Cos(heading));
             this.velocity.Y = (float)(1 * Math.Sin(heading));
             this.targetPos = Target;
             this.animations = new Dictionary<AnimationKey, Animation>();
             this.Explosion_animations = new Dictionary<AnimationKey, Animation>();
             this.start = StartPos;
             this.ArcheryTarget = ArrowTarget;
 
        }
       /* public Projectiles(String CharacterName, Texture2D ProjectileTexture, double desiredHeading, Vector2 StartPos)
        {
            this.Speed = 6;
            this.name = CharacterName + "_projectile";
            this.heading = desiredHeading;
            this.velocity.X = (float)(1 * Math.Cos(heading));
            this.velocity.Y = (float)(1 * Math.Sin(heading));
            this.animations = new Dictionary<AnimationKey, Animation>();
            this.Explosion_animations = new Dictionary<AnimationKey, Animation>();
            this.start = StartPos;


        }*/
        #endregion

        #region Initialization Region
        // initialization
        #endregion

        #region Method Region
        public void load(Game game)
        {
            this.g = game;
            this.SpriteSheet = game.Content.Load<Texture2D>(@"Sprites\fireball");
            this.ArrowSheet = game.Content.Load<Texture2D>(@"Sprites\arrow");
            
            //Loads the fireball animation
            if (this.name.First() == 'F' || this.name.First() == 'R') //F for Forsaken, R for Rand
            {
                Animation animation = new Animation(8, 64, 64, 0, 0);
                this.animations.Add(AnimationKey.Left, animation);

                animation = new Animation(8, 64, 64, 0, 64);
                this.animations.Add(AnimationKey.UpPlusHalf, animation);

                animation = new Animation(8, 64, 64, 0, 128);
                this.animations.Add(AnimationKey.Up, animation);

                animation = new Animation(8, 64, 64, 0, 192);
                this.animations.Add(AnimationKey.RightPlusHalf, animation);

                animation = new Animation(8, 64, 64, 0, 256);
                this.animations.Add(AnimationKey.Right, animation);

                animation = new Animation(8, 64, 64, 0, 320);
                this.animations.Add(AnimationKey.DownPlusHalf, animation);

                animation = new Animation(8, 64, 64, 0, 384);
                this.animations.Add(AnimationKey.Down, animation);

                animation = new Animation(8, 64, 64, 0, 448);
                this.animations.Add(AnimationKey.LeftPlusHalf, animation);


                this.sprite = new AnimatedSprite(this.name, SpriteSheet, this.animations);
                this.sprite.heading = this.heading;
                this.sprite.velocity = this.velocity;
                this.sprite.Position = this.start;
            }
            else if (this.name.First() == 'A') //A for Aiel Archer
            {
                Animation animation = new Animation(1, 40, 40, 0, 0);
                this.animations.Add(AnimationKey.Up, animation);

                animation = new Animation(1, 40, 40, 0, 40);
                this.animations.Add(AnimationKey.UpPlusHalf, animation);

                animation = new Animation(1, 40, 40, 0, 80);
                this.animations.Add(AnimationKey.Left, animation);

                animation = new Animation(1, 40, 40, 0, 120);
                this.animations.Add(AnimationKey.LeftPlusHalf, animation);

                animation = new Animation(1, 40, 40, 0, 160);
                this.animations.Add(AnimationKey.Down, animation);

                animation = new Animation(1, 40, 40, 0, 200);
                this.animations.Add(AnimationKey.DownPlusHalf, animation);

                animation = new Animation(1, 40, 40, 0, 240);
                this.animations.Add(AnimationKey.Right, animation);

                animation = new Animation(1, 40, 40, 0, 280);
                this.animations.Add(AnimationKey.RightPlusHalf, animation);


                this.sprite = new AnimatedSprite(this.name, ArrowSheet, this.animations);
                this.sprite.heading = this.heading;
                this.sprite.velocity = this.velocity;
                this.sprite.Position = this.start;
            }


        }
        // Update
        public void Update(GameTime gameTime, List<Ally> ArmyOfTheDragon, List<Enemy> ArmyOfTheDarkLord, List<Projectiles> ActiveProjectiles,
                            List<Explosion> ActiveExplosions, Player Rand)
  {
            if (this.sprite.name.First() == 'A')
            {
                distanceX = (this.ArcheryTarget.Position.X - this.sprite.Position.X) * (ArcheryTarget.Position.X - this.sprite.Position.X);
                distanceY = (ArcheryTarget.Position.Y - this.sprite.Position.Y) * (ArcheryTarget.Position.Y - this.sprite.Position.Y);
                this.PosDiff = ArcheryTarget.Position - this.sprite.Position;
                this.desiredHeading = Math.Atan2(this.PosDiff.Y, this.PosDiff.X);
                this.heading = this.desiredHeading * -180 / Math.PI;
                this.sprite.velocity.X = (float)(1 * Math.Cos(this.desiredHeading));
                this.sprite.velocity.Y = (float)(1 * Math.Sin(this.desiredHeading));
            }
            else if (this.sprite.name.First() == 'F')
            {
                distanceX = (targetPos.X - this.sprite.Position.X) * (targetPos.X - this.sprite.Position.X);
                distanceY = (targetPos.Y - this.sprite.Position.Y) * (targetPos.Y - this.sprite.Position.Y);
                heading = this.sprite.heading * -180 / Math.PI;
            }

           
            if (this.heading < 0)
            {
                this.heading = 360 + this.heading;
            }
            
            if (heading < 22 || heading >= (337))
            {
                this.sprite.CurrentAnimation = AnimationKey.Right;
            }
            else if (heading < 67 && heading >= (22))
            {
                this.sprite.CurrentAnimation = AnimationKey.RightPlusHalf;
            }
            else if (heading < 112 && heading >= (67))
            {
                this.sprite.CurrentAnimation = AnimationKey.Up;
            }
            else if (heading < 157 && heading >= (112))
            {
                this.sprite.CurrentAnimation = AnimationKey.UpPlusHalf;
            }
            else if (heading < 202 && heading >= (157))
            {
                this.sprite.CurrentAnimation = AnimationKey.Left;
            }
            else if (heading < 247 && heading >= (202))
            {
                this.sprite.CurrentAnimation = AnimationKey.LeftPlusHalf;
            }
            else if (heading < 292 && heading >= (247))
            {
                this.sprite.CurrentAnimation = AnimationKey.Down;
            }
            else if (heading < 337 && heading >= (292))
            {
                this.sprite.CurrentAnimation = AnimationKey.DownPlusHalf;
            }
            if (this.name.First() == 'R')
            {

                this.sprite.velocity.X = this.velocity.X;
                this.sprite.velocity.Y = this.velocity.Y;
                this.sprite.isAnimating = true;
                //this.sprite.velocity.Normalize();
                this.sprite.Position += this.sprite.velocity * this.Speed;
                this.sprite.LockToMap();
            }
            else if (this.name.First() == 'F')
            {
                if ((distanceX + distanceY) <= 100 && this.expl == null)
                {
                    this.sprite.velocity.X = this.velocity.X = 0;
                    this.sprite.velocity.Y = this.velocity.Y = 0;
                    //ActiveProjectiles.Remove(this);
                    this.active = false;
                    foreach (Enemy s in ArmyOfTheDarkLord)
                    {
                        if ((Math.Abs(s.spriteWalk.Position.X - this.sprite.Position.X) < 50) && Math.Abs(s.spriteWalk.Position.Y - this.sprite.Position.Y) < 50)
                        {
                            s.spriteWalk.health -= 30;
                        }
                    }
                    foreach (Ally s in ArmyOfTheDragon)
                    {
                        if ((Math.Abs(s.spriteWalk.Position.X - this.sprite.Position.X) < 50) && Math.Abs(s.spriteWalk.Position.Y - this.sprite.Position.Y) < 50)
                        {
                            s.spriteWalk.health -= 30;
                        }
                    }
                    if ((Math.Abs(Rand.sprite.Position.X - this.sprite.Position.X) < 50) && Math.Abs(Rand.sprite.Position.Y - this.sprite.Position.Y) < 50)
                    {
                        Rand.sprite.health -= 30;
                    }
                    this.expl = new Explosion(this.sprite.name, this.sprite.Position);
                    ActiveExplosions.Add(this.expl);
                    this.expl.load(this.g);
                    this.expl.Update(gameTime, ActiveExplosions);

                    this.sprite.isAnimating = false;
                    this.sprite = null;
                }
                else if (this.expl != null)
                {
                    if (this.expl.sprite == null || this.expl.sprite.isAnimating == false)
                    {
                        this.expl = null;
                        GC.Collect();
                        GC.WaitForPendingFinalizers();
                    }
                }

                else
                {
                    this.sprite.isAnimating = true;
                    //this.sprite.velocity.Normalize();
                    this.sprite.Position += this.velocity * 8;
                    this.sprite.LockToMap();
                }
            }
            else if (this.name.First() == 'A')
            {
                if ((distanceX + distanceY) <= 500)
                {
                    this.sprite.velocity.X = this.velocity.X = 0;
                    this.sprite.velocity.Y = this.velocity.Y = 0;
                    //ActiveProjectiles.Remove(this);
                    this.active = false;
                   
                    ArcheryTarget.health -= 20;
                    

                    this.sprite.isAnimating = false;
                    this.sprite = null;
                }
                else if (((this.sprite.Position.X - this.start.X) * (this.sprite.Position.X - this.start.X) + (this.sprite.Position.Y - this.start.Y) * (this.sprite.Position.Y - this.start.Y)) > 30000)
                {
                    this.sprite.velocity.X = this.velocity.X = 0;
                    this.sprite.velocity.Y = this.velocity.Y = 0;
                    this.sprite.isAnimating = false;
                    this.sprite = null;
                    this.active = false;
                }
                else
                {
                    this.sprite.isAnimating = true;
                    this.sprite.velocity.Normalize();
                    this.sprite.Position += this.velocity * this.Speed;
                    this.sprite.LockToMap();
                }
            }
            if( this.sprite != null)
            this.sprite.Update(gameTime);
        }
        // Draw
        public void Draw(GameTime gameTime, SpriteBatch spriteBatch, Game1 GameRef)
        {
            if( this.sprite != null)
            this.sprite.Draw(gameTime, GameRef.SpriteBatch, Player.camera);
        }
        #endregion
        ~Projectiles()
        {
            this.animations = null;
            this.Explosion_animations = null;
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }

    }

}
