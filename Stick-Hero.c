//Nick Cheung Stick Ninja Game in C using Processing

PImage backgroundPic, characterPic; //variables for the pictures
PFont font1; //variable for the font
float characterPicX = 185; //variables for location of different shapes
float characterPicY = 375;
float lineX1 = 215;
float lineY1 = 410;
float lineX2 = 215;
float lineY2 = 410;
float hypot = 0;
float rect1X, rect1Y, rect1Width, rect2X, rect2Y, rect2Width;
float redSquare1X, redSquare2X; 
int score1 = 0; //varables for the score
int score2 = 0;
int score3 = 0;
int score;
int scoreX = 200; //location of the scores
int highScoreX = 1000;
int highScore1X = 1000;
int highScore2X = 1000;
int highScore3X = 1000;
int welcomeTextX = 200;
int clickTextX = 200; //location of texts
int circleX = 200;
int loseTextX = 401;
boolean bridgeTouch = false; //booleans to say when something is true/false
boolean bridgeTouchRed = false;
boolean bridgeUp = false;
boolean spaceReleased = false;
boolean spaceReleasedTime = true;
boolean rect1Move = true;
boolean rect2Move = true;
boolean characterMove = true;
boolean characterMoveStart = true;
boolean mode2Start = true;
boolean mode3Start = true;
boolean gameStart = true;
int[] highScore = {0, 0, 0, 0}; //array for the highscores
int screenMode = 0; // integer for the different screen modes
float theta = PI;  // float for the angle theta, which is pi

void setup() {
  size(400, 600); // sets canvas size
}

void draw() {
  backgroundPic = loadImage("backgroundPic.jpg"); //loads in background image (in draw so it is redrawn with every loop)
  imageMode(CORNER); //makes it so the coordinates are the corners
  image(backgroundPic, -75, 0, 575, 800); //sets coordinate values

  noStroke();
  fill(255, 200, 0);
  circle(circleX, 140, 150); //creates yellow circle

  font1 = loadFont("Tahoma-Bold-48.vlw");
  textSize(30);
  fill(0);
  textAlign(CENTER);
  text("CLICK", clickTextX, 125);
  text("TO PLAY!", clickTextX, 165); //text in the circle

  textSize(20);
  fill(0);
  textAlign(CENTER);
  text("Welcome! Hold the space bar to build.", welcomeTextX, 35); //welcome text at the top

  textSize(30);
  fill(0);
  textAlign(CENTER);
  text("SCORE: " + (score1 + score2 + score3), scoreX, 125); //displays the score
  
  textSize(15);
  fill(0);
  textAlign(CENTER);
  text("HIGHSCORES:", highScoreX, 305); //displays the highscores

  textSize(15);
  fill(0);
  textAlign(CENTER);
  text("#1: " + highScore[3], highScore1X, 320);
  text("#2: " + highScore[2], highScore2X, 335);
  text("#3: " + highScore[1], highScore3X, 350);

  textSize(40);
  fill(0);
  textAlign(CENTER);
  text("YOU LOSE :(", loseTextX, 275); //you lose text

  characterPic = loadImage("characterPic.png"); //loads in character image
  imageMode(CORNERS);
  image(characterPic, characterPicX, characterPicY, characterPicX + 30, characterPicY + 50);

  stroke(100);
  fill(100);
  rect(rect1X, rect1Y, rect1Width, 800); //creates 1st rect 

  redSquare1X = rect1X + rect1Width/2 - 5;
  noStroke();
  fill(255, 0, 0);
  square(redSquare1X, rect1Y - 1, 10); //creates red square in the middle of rect1

  stroke(100);
  fill(100);
  rect(rect2X, rect2Y, rect2Width, 800); //creates 2nd rect

  redSquare2X = rect2X + rect2Width/2 - 5;
  noStroke();
  fill(255, 0, 0);
  square(redSquare2X, rect2Y - 1, 10); //creates red square in the middle of rect2

  strokeWeight(3);
  stroke(0, 0, 255);
  line(lineX1, lineY1, lineX2, lineY2); //creates the bridge player grows

  score = score1 + score2 + score3; //makes the score equal to the sum of each score (didn't work when I only had one score variable)

  if (screenMode == 0) { // sets all the variables to what they should be at the start
    circleX = 200; //200 means it is being displayed
    clickTextX = 200;
    welcomeTextX = 200;  
    loseTextX = 1000; //anything greater than 400 means it is not being displayed
    rect2X = 1000;
    rect2Y = 412;
    rect2Width = 100;

    rect1X = 150;
    rect1Y = 412;
    rect1Width = 100;

    lineX1 = 215;
    lineY1 = 410;
    lineX2 = 215;
    lineY2 = 410;
    theta = PI;

    bridgeTouch = false;
    bridgeUp = false;
    spaceReleased = false;
    rect1Move = true;
    characterMove = true;
    characterMoveStart = false;
    spaceReleasedTime = true;

    score1 = 0;
    score2 = 0;
    score3 = 0;

    scoreX = 1000;
    highScoreX = 1000;
    highScore1X = 1000;
    highScore2X = 1000;
    highScore3X = 1000;

    start(); //sends to a new void that changes screenMode to 1 if the mouse is pressed
    
  } else if (screenMode == 1) {
    circleX = 1000; //moves variables onto/out of the screen
    clickTextX = 1000;
    welcomeTextX = 1000;  
    loseTextX = 1000;
    scoreX = 200;
    highScoreX = 1000;
    highScore1X = 1000;
    highScore2X = 1000;
    highScore3X = 1000;

    if (gameStart == true) { //sets variables at the start (can change within this thread)
      lineX1 = 215;
      lineY1 = 410;
      lineX2 = 215;
      lineY2 = 410;
      theta = PI;

      rect1X = 150;
      rect1Y = 412;
      rect1Width = 100;

      bridgeTouch = false;
      bridgeUp = false;
      spaceReleased = false;
      rect1Move = true;
      characterMove = true;
      characterMoveStart = false;
      gameStart = false;
    }

    if (theta == PI) { //makes it so that the line can grow as the hypot grows
      lineY2 = lineY1 - hypot;
    }

    if (characterPicX >= 73 && rect1Move == true) { //moves rect1, the character, and the line to the left and allows the user to grow the bridge
      characterPicX -= 3.5;
      rect1X -= 3.5;
      lineX1 -=3.5;
      lineX2 -=3.5;
      bridgeUp = true;

      if (characterPicX == 73) { //if the character arrives at 73, a new rect is made a random distance away with random width
        rect2X = (rect1X + rect1Width) + random(10, 200);
        rect2Y = 412;
        rect2Width = random(20, 100);
        rect1Move = false; //doesn't let rect1 move again
      }
    }

    if (keyPressed) {
      if (key == ' ' && bridgeUp == true) { //if the space bar is being pressed, the line grows
        hypot += 3.5;
      }
    }

// if the space bar is released...
    if (spaceReleasedTime == true && spaceReleased == true && theta < 3 * HALF_PI) { 
      lineX1 = 401; //moves the line out of the screen
      lineX2 = 1000;
      theta += 0.1; //increases theta
      translate(103, 410); //moves axis of rotation to right infront of the character
      rotate(theta); //rotates a distance of theta
      rect(0, 0, 1, hypot); //creates a rect that rotates
      lineY2 = 410;
      if (theta == 4.7415915) { //if theta is closest to 3π/2, the line comes back
        lineX1 = 103;
        lineX2 = 100 + hypot; 
        lineY1 = 410;
      }
      delay(5); //makes the rotation slower
    }

    if (lineX2 >= rect2X && lineX2 <= rect2X + rect2Width && rect1Move == false) {
      bridgeTouch = true; //if the line can touch the platform, then bridgeTouch is true
    } else {
      bridgeTouch = false;//else it's false
    }

    if (lineX2 >= redSquare2X && lineX2 <= redSquare2X + 10 + rect2Width && rect1Move == false && spaceReleased == true) {
      bridgeTouchRed = true; //if line is within the red square, then bridgeTouchRed is true
    } else {
      bridgeTouchRed = false; //else it's false
    }

    if (bridgeTouch == true && characterPicX <= lineX2) {
      characterPicX += 3; //moves the character to the end of the line
    }

    if (characterPicX >= lineX2 && characterPicX <= lineX2 + 3  && bridgeTouch == true) {
      characterMove = false;
      screenMode = 2;
      mode2Start = true; //sends to mode2
    }

    if (characterMove == false && lineX2 >= rect2X && lineX2 <= rect2X + rect2Width) {
      score1++; //increases the score by 1
    }

    if (characterMove == false && lineX2 >= rect2X && lineX2 <= rect2X + rect2Width && bridgeTouchRed == true) {
      score1++; //increases the score by another 1 (2 total)
    }

    if (bridgeTouch == false && bridgeUp == false) {
      if (characterPicX <= lineX2 && rect1Move == false) {
        characterPicX +=3; //moves character to the end of line
      }
      if (characterPicX >= lineX2 && characterPicX <= lineX2 + 3 && rect1Move == false) {
        characterPicY += 7.5; //makes character fall out of screen
      }
    }
  } else if (screenMode == 2) {  
    if (mode2Start == true) { //resets variables once
      theta = PI;
      hypot = 0;
      rect1Move = true;
      lineX1 = characterPicX + 30;
      lineX2 = characterPicX + 30;
      highScoreX = 1000;
      highScore1X = 1000;
      highScore2X = 1000;
      highScore3X = 1000;
      spaceReleasedTime = false;
      mode2Start = false;
    }

    if (characterPicX >= 73 && rect2Move == true) { //moves rects and character to the left
      characterPicX -= 3.5;
      rect2X -= 3.5;
      rect1X -= 3.5;
      lineX1 -= 3.5;
      lineX2 -= 3.5;
      bridgeUp = true;
    }

    if (characterPicX <= 73 && characterPicX >= 70) { //stops rect2
      rect2Move = false;
    }

    if (rect1X < 0) { //creates a new rect a random distance away with a random width
      rect1X = (rect2X + rect2Width) + random(10, 200);
      rect1Y = 412;
      rect1Width = random(20, 100);
    }

    if (theta == PI) { //allows the line to grow
      lineY2 = lineY1 - hypot;
    }

//repeats previous logic with different variables
    if (keyPressed) { 
      if (key == ' ' && bridgeUp == true) {
        hypot += 3.5;
        characterMove = true;
      }
    }

    if (spaceReleasedTime == true && spaceReleased == true && theta < 3 * HALF_PI) { 
      lineX1 = 401;
      lineX2 = 1000;
      lineY2 = 410;
      theta += 0.1;
      translate(103, 410);
      rotate(theta);
      rect(0, 0, 1, hypot); 
      if (theta == 4.7415915) {
        lineX1 = 103;
        lineX2 = 100 + hypot; 
        lineY1 = 410;
      }
      delay(5);
    }

    if (lineX2 >= rect1X && lineX2 <= rect1X + rect1Width && rect2Move == false && spaceReleased == true) {
      bridgeTouch = true;
    } else {
      bridgeTouch = false;
    }

    if (lineX2 >= redSquare1X && lineX2 <= redSquare1X + 10 + rect1Width && rect2Move == false && spaceReleased == true) {
      bridgeTouchRed = true;
    } else {
      bridgeTouchRed = false;
    }

    if (bridgeTouch == true && characterPicX <= lineX2) {
      characterPicX += 3;
    }

    if (characterPicX >= lineX2 && characterPicX <= lineX2 + 3 && bridgeTouch == true) {
      characterMove = false;
      screenMode = 3; //sends to mode 3
      mode3Start = true;
    }

    if (characterMove == false && lineX2 >= rect1X && lineX2 <= rect1X + rect1Width) {
      score2++;
    }
    if (characterMove == false && lineX2 >= rect1X && lineX2 <= rect1X + rect1Width && bridgeTouchRed == true) {
      score2++;
    }

    if (bridgeTouch == false && bridgeUp == false) {
      if (characterPicX <= lineX2 && rect2Move == false) {
        characterPicX +=3;
      }
      if (characterPicX >= lineX2 && characterPicX <= lineX2 + 3 && rect2Move == false) {
        characterPicY += 7.5;
      }
    }
  } else if (screenMode == 3) {
    if (mode3Start == true) { //resets variables once
      theta = PI;
      hypot = 0;
      rect2Move = true;
      lineX1 = characterPicX + 30;
      lineX2 = characterPicX + 30;
      spaceReleasedTime = false;
      mode3Start = false;
    }

//repeats previous logic with different variables
    if (characterPicX >= 73 && rect1Move == true) { 
      characterPicX -= 3.5;
      rect2X -= 3.5;
      rect1X -= 3.5;
      lineX1 -= 3.5;
      lineX2 -= 3.5;
      bridgeUp = true;
    }

    if (characterPicX <= 73 && characterPicX >= 70) {
      rect1Move = false;
    }

    if (rect2X < 0) {
      rect2X = (rect1X + rect1Width) + random(10, 200);
      rect2Y = 412;
      rect2Width = random(20, 100);
    }

    if (theta == PI) {
      lineY2 = lineY1 - hypot;
    }

    if (keyPressed) {
      if (key == ' ' && bridgeUp == true) {
        hypot += 3.5;
        characterMove = true;
      }
    }

    if (spaceReleasedTime == true && spaceReleased == true && theta < 3 * HALF_PI) {
      lineX1 = 401;
      lineX2 = 1000;
      theta += 0.1;
      translate(103, 410);
      rotate(theta);
      rect(0, 0, 1, hypot); 
      lineY2 = 410;
      if (theta == 4.7415915) {
        lineX1 = 103;
        lineX2 = 100 + hypot; 
        lineY1 = 410;
      }
      delay(5);
    }

    if (lineX2 >= rect2X && lineX2 <= rect2X + rect2Width && rect1Move == false && spaceReleased == true) {
      bridgeTouch = true;
    } else {
      bridgeTouch = false;
    }

    if (lineX2 >= redSquare2X && lineX2 <= redSquare2X + 10 + rect2Width && rect1Move == false && spaceReleased == true) {
      bridgeTouchRed = true;
    } else {
      bridgeTouchRed = false;
    }

    if (bridgeTouch == true && characterPicX <= lineX2) {
      characterPicX += 3;
    }

    if (characterPicX >= lineX2 && characterPicX <= lineX2 + 3 && bridgeTouch == true) {
      characterMove = false;
      screenMode = 2; //sends back to mode 2
      mode2Start = true;
    }

    if (characterMove == false && lineX2 >= rect2X && lineX2 <= rect2X + rect2Width) {
      score3++;
    }
    if (characterMove == false && lineX2 >= rect2X && lineX2 <= rect2X + rect2Width && bridgeTouchRed == true) {
      score3++;
    }

    if (bridgeTouch == false && bridgeUp == false) {
      if (characterPicX <= lineX2 && rect1Move == false) {
        characterPicX +=3;
      }
      if (characterPicX >= lineX2 && characterPicX <= lineX2 + 3 && rect1Move == false) {
        characterPicY += 7.5;
      }
    }
  } else if (screenMode == 4) {
    circleX = 200; //sets variables for lose screen
    clickTextX = 200; //200 means on the canvas
    welcomeTextX = 1000;  //anything >400 is off of the canvas
    loseTextX = 200;
    rect2X = 1000;
    rect2Y = 412;
    rect2Width = 100;

    characterPicX = 185;
    characterPicY = 375;
    lineX1 = characterPicX + 30;
    lineY1 = 410;
    lineX2 = lineX1;
    lineY2 = 410;
    hypot = 0;
    theta = PI;

    rect1X = 150;
    rect1Y = 412;
    rect1Width = 100;

    scoreX = 1000;
    highScoreX = 200;
    highScore1X = 200;
    highScore2X = 200;
    highScore3X = 200;
    score = highScore[0];
    
    //for (int i = 0; i <= 3; i++){
    //    if (highScore[i] >= highScore[i + 1]){
    //      score = highScore[i + 1];
    //    } else {
    //      score = highScore[i];
    //    }
    //  }

    bridgeUp = true;
    rect1Move = true;
    characterMoveStart = true;
    spaceReleasedTime = true;

    start(); //allows the code to restart with a mouse press
  }

  if (characterPicY > height) {
    screenMode = 4; //if the character falls of the screen, go to mode 4
  }
  println(characterMove);
}

void keyReleased() {
  spaceReleased = true; //if key released, then booleans change allowing the blue rect to rotate
  spaceReleasedTime = true;
  bridgeUp = false;
}

void start() {
  if (mousePressed) { //starts/restarts the game with a mouse press
    screenMode = 1;
    gameStart = true;
    score1 = 0; //resets score
    score2 = 0;
    score3 = 0;
  }
}