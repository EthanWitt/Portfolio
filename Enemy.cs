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
    public enum enemies{AielSpearman, AielArcher, Forsaken, WiseWoman}
    class Enemy
    {
        #region Field Region
        Game1 gameRef;
        Texture2D spriteSheet, spriteSheetAttack;
        bool attack = false;
        int index, health = 100;
        int targetted = 0, range;
        float distanceX, distanceY;
        double desiredHeading, temp;
        bool targetting = false;
        AnimatedSprite target;
        public AnimatedSprite sprite;
        Vector2 diff;
        Vector2 PosDiff;
        Vector2 InitPos, InitVel;
        public Dictionary<AnimationKey, Animation> animationsA;
        public Dictionary<AnimationKey, Animation> animationsW;



        #endregion

        #region Constructor Region
        public Enemy(Game game, List<AnimatedSprite> ArmyOfTheDragon)
        {
            gameRef = (Game1)game;
            this.attack = false;
            this.index = 0;
            this.InitPos.X = 400;
            this.InitPos.Y = 400;
            this.target = null;
            this.range = 8000;
            this.animationsA = new Dictionary<AnimationKey,Animation>();
            this.animationsW = new Dictionary<AnimationKey,Animation>();


        }
        #endregion

        #region Method Region
        public void setEnemy(Texture2D Sheet)
        {
            spriteSheet = Sheet;
        }
        public void load(Game game,Dictionary<AnimationKey, Animation> animationsA, Dictionary<AnimationKey, Animation> animationsW)
        {
            this.spriteSheet = game.Content.Load<Texture2D>(@"Sprites\Mage_walk_animation copy");
            this.spriteSheetAttack = game.Content.Load<Texture2D>(@"Sprites\Mage_attack_animation complete");
            Animation animationWalk = new Animation(9, 64, 64, 0, 0);
            Animation animationAttack = new Animation(7, 64, 64, 0, 0);
            
            animationsW.Add(AnimationKey.Down, animationWalk);
            animationsA.Add(AnimationKey.Up, animationAttack);

            animationWalk = new Animation(9, 64, 64, 0, 320);
            animationsW.Add(AnimationKey.Left, animationWalk);

            animationWalk = new Animation(9, 64, 64, 0, 448);
            animationsW.Add(AnimationKey.Right, animationWalk);

            animationWalk = new Animation(9, 64, 64, 0, 256);
            animationsW.Add(AnimationKey.Up, animationWalk);

            animationAttack = new Animation(7, 64, 64, 0, 128);
            animationsA.Add(AnimationKey.Down, animationAttack);

            animationAttack = new Animation(7, 64, 64, 0, 64);
            animationsA.Add(AnimationKey.Left, animationAttack);

            animationAttack = new Animation(7, 64, 64, 0, 191);
            animationsA.Add(AnimationKey.Right, animationAttack);

            this.sprite = new AnimatedSprite(spriteSheetAttack, animationsA);
            this.sprite = new AnimatedSprite(spriteSheet, animationsW);

            this.target = new AnimatedSprite(spriteSheet, animationsW);
            this.sprite.Position = InitPos;
            this.InitVel.X = 0;
            this.InitVel.Y = 0;
            this.sprite.velocity = InitVel;

        }
        public void Update(GameTime gameTime, List<AnimatedSprite> ArmyOfTheDragon, Dictionary<AnimationKey, Animation> animations, Dictionary<AnimationKey, Animation> animationsA)
        {

            //call AI
            Path(ArmyOfTheDragon, animations, animationsA);

            //update
            this.sprite.Update(gameTime);
        }
        public void Draw(GameTime gameTime, SpriteBatch spriteBatch, Game1 GameRef)
        {
            this.sprite.Draw(gameTime, GameRef.SpriteBatch, Player.camera);
        }

        #endregion

        #region AI Region
        public void Path(List<AnimatedSprite> ArmyOfTheDragon, Dictionary<AnimationKey, Animation> animations, Dictionary<AnimationKey, Animation> animationsA)
        {
            if (targetting == false)
            {
                ArmyOfTheDragon.ForEach(delegate(AnimatedSprite s)
                {
                    if (s != null && s != this.sprite)
                    {
                        distanceX = (s.Position.X - this.sprite.Position.X) * (s.Position.X - this.sprite.Position.X);
                        distanceY = (s.Position.Y - this.sprite.Position.Y) * (s.Position.Y - this.sprite.Position.Y);

                        if (targetting == false && distanceX + distanceY < this.range && s.targetted < 3 && s.health > 0)
                        {
                            targetting = true;
                            s.targetted += 1;

                            this.target = s;
                        }
                    }

                });
            }
            else
            {
                if (target.health <= 0)
                {
                    targetting = false;
                }

                distanceX = (target.Position.X - this.sprite.Position.X) * (target.Position.X - this.sprite.Position.X);
                distanceY = (target.Position.Y - this.sprite.Position.Y) * (target.Position.Y - this.sprite.Position.Y);
                this.diff.X = distanceX;
                this.diff.Y = distanceY;
                this.PosDiff = target.Position - this.sprite.Position;

                this.desiredHeading = -Math.Atan2(this.PosDiff.Y, this.PosDiff.X);
                this.temp = this.desiredHeading * 180 / Math.PI;

                this.attack = false;
                this.sprite.Change(this.spriteSheet, this.animationsW, this.sprite.animations);
                this.sprite.velocity.X = (float)(1 * Math.Cos(this.desiredHeading));
                this.sprite.velocity.Y = (float)(1 * Math.Sin(this.desiredHeading));

                if (this.temp > 315 && this.temp <= 45)
                    {
                        this.sprite.heading = 0;
                        //this.sprite.velocity.X = 1;
                    }
                else if (this.temp > 45 && this.temp <= 135)
                    {
                        this.sprite.heading = 90;
                    }
                else if (this.temp > 135 && this.temp <= 225)
                    {
                        this.sprite.heading = 180;
                      
                    }
                else if (this.temp > 225 && this.temp <= 315)
                    {
                        this.sprite.heading = 270;
                        
                    }

                if (this.sprite.velocity != Vector2.Zero )
                {
                    if (this.sprite.heading == 0)
                    {
                        sprite.CurrentAnimation = AnimationKey.Right;
                        this.sprite.velocity.X = -1;
                    }
                    else if (this.sprite.heading == 90)
                    {
                        sprite.CurrentAnimation = AnimationKey.Up;
                        this.sprite.velocity.Y = -1;
                    }
                    else if (this.sprite.heading == 180)
                    {
                        sprite.CurrentAnimation = AnimationKey.Left;
                        this.sprite.velocity.X = -1;
                    }
                    else
                    {
                        sprite.CurrentAnimation = AnimationKey.Down;
                        this.sprite.velocity.Y = 1;
                    }
                    this.sprite.IsAnimating = true;
                    this.sprite.velocity.Normalize();

                    this.sprite.Position += this.sprite.velocity * this.sprite.Speed;
                    this.sprite.LockToMap();

                }

               else
                {
                    this.sprite.IsAnimating = false;

                    this.sprite.velocity.X = 0;
                    this.sprite.velocity.Y = 0;
                    this.sprite.velocity.Normalize();
                    this.sprite.Position += sprite.velocity * sprite.Speed;
                    this.sprite.LockToMap();


                }
            }

        }
        #endregion
    }
}
