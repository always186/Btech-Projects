import numpy as np #numerical python library
import cv2 #computer vision
import time
import win32api, win32con

cap = cv2.VideoCapture(0)
time.sleep(2)
ret, frame = cap.read()

lower1=[157,69,119]
upper1=[179,255,255]
lower2=[157,69,119]
upper2=[179,255,255]

while(1):
    ret, frame = cap.read()
    frame = cv2.resize(frame,(1360, 750), interpolation = cv2.INTER_CUBIC)
    frame=cv2.flip(frame,1)
    #cv2.imshow("Original Frame", frame)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV) # h->hue, s->saturation, v->value --------- In HSV, it is more easier to represent a color than in BGR color-space
    #cv2.imshow("HSV Frame", hsv)
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
            win32api.SetCursorPos((int(x), int(y)))
            #use int(y) for paddle 1
            cv2.circle(frame, center, 5, (0, 0, 255), -1)
    if len(cnts2) > 0:
        c = max(cnts2, key=cv2.contourArea)
        ((x, y), radius) = cv2.minEnclosingCircle(c)
        M = cv2.moments(c)
        center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
        if radius > 10:
            cv2.circle(frame, (int(x), int(y)), int(radius),
                (0, 255, 255), 2)
            win32api.SetCursorPos((int(x), int(y)))
            #use int(y) for paddle 1
            cv2.circle(frame, center, 5, (0, 0, 255), -1)
    cv2.imshow("Frame", frame)
    if cv2.waitKey(1) == 27:
        break
cap.release()
cv2.destroyAllWindows()
