import kivy
kivy.require('1.1.1')

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.properties import NumericProperty, ReferenceListProperty,\
    ObjectProperty
from kivy.vector import Vector
from kivy.clock import Clock
import numpy as np #numerical python library
import cv2 #computer vision
import time
red=0
blue=0
cap = cv2.VideoCapture(0)
time.sleep(2)
ret, frame = cap.read()
lower1=[157,69,119]
upper1=[179,255,255]
lower2=[157,69,119]
upper2=[179,255,255]

def vid_process():
    global red, blue, cap, ret, frame, lower1, upper1, lower2, upper2
    ret, frame = cap.read()
    frame = cv2.resize(frame,(1360, 750), interpolation = cv2.INTER_CUBIC)
    frame=cv2.flip(frame,1)
    cv2.imshow("Original Frame", frame)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV) # h->hue, s->saturation, v->value --------- In HSV, it is more easier to represent a color than in BGR color-space
    cv2.imshow("HSV Frame", hsv)
    lower1 = np.array(lower1)    
    upper1 = np.array(upper1)
    lower2 = np.array(lower2)    
    upper2 = np.array(upper2)
    mask1  = cv2.inRange(hsv, lower1, upper1)
    mask1 = cv2.erode(mask1, None, iterations=2)
    mask1 = cv2.dilate(mask1, None, iterations=2)
    mask1 = cv2.medianBlur(mask1,5)
    mask2  = cv2.inRange(hsv, lower2, upper2)
    mask2 = cv2.erode(mask2, None, iterations=2)
    mask2 = cv2.dilate(mask2, None, iterations=2)
    mask2 = cv2.medianBlur(mask2,5)
    #cv2.imshow("Region of Interest", mask)
    cnts1 = cv2.findContours(mask1.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)[-2]
    cnts2 = cv2.findContours(mask2.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)[-2]
    center = None
    if len(cnts1) > 0:
        c = max(cnts1, key=cv2.contourArea)
        ((x, y), radius) = cv2.minEnclosingCircle(c)
        M = cv2.moments(c)
        center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
        if radius > 10:
            cv2.circle(frame, (int(x), int(y)), int(radius),
                (0, 255, 255), 2)
            red=int(y)
            cv2.circle(frame, center, 5, (0, 0, 255), -1)
    if len(cnts2) > 0:
        c = max(cnts2, key=cv2.contourArea)
        ((x, y), radius) = cv2.minEnclosingCircle(c)
        M = cv2.moments(c)
        center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
        if radius > 10:
            cv2.circle(frame, (int(x), int(y)), int(radius),
                (0, 255, 255), 2)
            blue=int(y)
            cv2.circle(frame, center, 5, (0, 0, 255), -1)
    cv2.imshow("Frame", frame)
    print red,blue
    return red,blue
    

class PongPaddle(Widget):
    score = NumericProperty(0)

    def bounce_ball(self, ball):
        if self.collide_widget(ball):
            vx, vy = ball.velocity
            offset = (ball.center_y - self.center_y) / (self.height / 2)
            bounced = Vector(-1 * vx, vy)
            vel = bounced * 1.1
            ball.velocity = vel.x, vel.y + offset


class PongBall(Widget):
    velocity_x = NumericProperty(0)
    velocity_y = NumericProperty(0)
    velocity = ReferenceListProperty(velocity_x, velocity_y)

    def move(self):
        self.pos = Vector(*self.velocity) + self.pos


class PongGame(Widget):
    ball = ObjectProperty(None)
    player1 = ObjectProperty(None)
    player2 = ObjectProperty(None)

    def serve_ball(self, vel=(4, 0)):
        self.ball.center = self.center
        self.ball.velocity = vel

    def update(self, dt):
        self.ball.move()

        # bounce ball off paddles
        self.player1.bounce_ball(self.ball)
        self.player2.bounce_ball(self.ball)

        # bounce ball off bottom or top
        if (self.ball.y < self.y) or (self.ball.top > self.top):
            self.ball.velocity_y *= -1

        # went off a side to score point?
        if self.ball.x < self.x:
            self.player2.score += 1
            self.serve_ball(vel=(4, 0))
        if self.ball.x > self.width:
            self.player1.score += 1
            self.serve_ball(vel=(-4, 0))

    def on_touch_move(self, touch):
        red, blue=vid_process()
        if touch.x < self.width / 3:
            self.player1.center_y = touch.y
        if touch.x > self.width - self.width / 3:
            self.player2.center_y = touch.y


class PongApp(App):
    def build(self):
        game = PongGame()
        game.serve_ball()
        Clock.schedule_interval(game.update, 1.0 / 60.0)
        return game


if __name__ == '__main__':
    PongApp().run()
    while(1):
        red, blue=vid_process()
        
