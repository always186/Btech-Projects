from collections import deque
import numpy as np
import argparse
import cv2
import time
from random import randint
import math
cap = cv2.VideoCapture(0)
time.sleep(2)
ret, frame = cap.read()
frame = cv2.resize(frame,(1360, 750), interpolation = cv2.INTER_CUBIC)
table=cv2.imread('table.png')
table = cv2.resize(table,(1360, 750), interpolation = cv2.INTER_CUBIC)

ap = argparse.ArgumentParser()
ap.add_argument("-b", "--buffer", type=int, default=5,help="50")
args = vars(ap.parse_args())
apg = argparse.ArgumentParser()
apg.add_argument("-b", "--buffer", type=int, default=5,help="50")
argsg = vars(apg.parse_args())

lower=[157,69,119]
upper=[179,255,255]
"""lowerg=[36,108,77]
upperg=[91,255,255]"""
#for green bead - good
#lower=[63,124,113]
#upper=[90,255,255]
#for yellow bead - mixed with pipes
lowerg=[0,0,0]
upperg=[0,0,0]
#for blue bead - fair
#lowerg=[109,121,85]
#upperg=[120,193,202]
#for pink Highlighter
#lowerg=[150,155,46]
#upperg=[179,255,255]
pts = deque(maxlen=args["buffer"])
ptsg = deque(maxlen=argsg["buffer"])
i=table.shape[::-1][1]/2
j=table.shape[::-1][2]/2
x=y=0


def kick(x,y,i,j):
    if math.sqrt(math.pow(x-i,2)+math.pow(y-j,2))<100:
        try:
            A=(y-j)/(x-i)
            b=(y-A*x)
            B=b-j
            P=math.pow(A,2)+1
            Q=2*(A*B-i)
            R=math.pow(i,2)+math.pow(B,2)-3600
            if x<=i and y<=j or x<i and y>j:
                i=(-Q+math.sqrt(Q*Q-4*P*R))/(2*P)
            else:
                i=(-Q-math.sqrt(Q*Q-4*P*R))/(2*P)
            j=A*i+b
        except:
            i=i
            j=j
        if i<30 or j<30 or i>1330 or j>720:
            i=table.shape[::-1][1]/2
            j=table.shape[::-1][2]/2
    return [i,j]

   


while(1):
    table=cv2.imread('table.png')
    table = cv2.resize(table,(1360, 750), interpolation = cv2.INTER_CUBIC)
    ret, frame = cap.read()
    frame = cv2.resize(frame,(1360, 750), interpolation = cv2.INTER_CUBIC)
    frame=cv2.flip(frame,1)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)


    lower = np.array(lower)    
    upper = np.array(upper)
    mask  = cv2.inRange(hsv, lower, upper)
    mask = cv2.erode(mask, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=2)
    mask = cv2.medianBlur(mask,5)
    cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)[-2]
    center = None
 
    # only proceed if at least one contour was found
    if len(cnts) > 0:
	    # find the largest contour in the mask, then use
	    # it to compute the minimum enclosing circle and
	    # centroid
	    c = max(cnts, key=cv2.contourArea)
	    ((x, y), radius) = cv2.minEnclosingCircle(c)
	    M = cv2.moments(c)
	    center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
 
	    # only proceed if the radius meets a minimum size
	    if radius > 10:
		    # draw the circle and centroid on the frame,
		    # then update the list of tracked points
		    cv2.circle(table, (int(x), int(y)), int(radius),(0, 255, 255), 2)
		    cv2.circle(table, center, 5, (0, 0, 255), -1)
    pts.appendleft(center)
    # loop over the set of tracked points
    for p in xrange(1, len(pts)):
        # if either of the tracked points are None, ignore
        # them
        if pts[p - 1] is None or pts[p] is None:
            continue 
	# otherwise, compute the thickness of the line and
	# draw the connecting lines
        thickness = int(np.sqrt(args["buffer"] / float(p + 1)) * 5)
        cv2.line(table, pts[p - 1], pts[p], (0, 0, 255), thickness)
        
    [i,j] = kick(x,y,i,j)
    #frame=cv2.bitwise_and(frame,frame,mask=mask)
    cv2.circle(table, (int(i),int(j)), 27, (255,0,255), -1)
    # show the frame to our screen
    cv2.imshow("play", table)

    lowerg = np.array(lowerg)    
    upperg = np.array(upperg)
    maskg  = cv2.inRange(hsv, lowerg, upperg)
    maskg = cv2.erode(maskg, None, iterations=2)
    maskg = cv2.dilate(maskg, None, iterations=2)
    maskg = cv2.medianBlur(maskg,5)
    cnts = cv2.findContours(maskg.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)[-2]
    center = None
 
    # only proceed if at least one contour was found
    if len(cnts) > 0:
	    # find the largest contour in the maskg, then use
	    # it to compute the minimum enclosing circle and
	    # centroid
	    c = max(cnts, key=cv2.contourArea)
	    ((x, y), radius) = cv2.minEnclosingCircle(c)
	    M = cv2.moments(c)
	    center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
 
	    # only proceed if the radius meets a minimum size
	    if radius > 10:
		    # draw the circle and centroid on the frame,
		    # then update the list of tracked points
		    cv2.circle(table, (int(x), int(y)), int(radius),(0, 255, 255), 2)
		    cv2.circle(table, center, 5, (255, 0, 0), -1)
    ptsg.appendleft(center)
    # loop over the set of tracked points
    for p in xrange(1, len(ptsg)):
        # if either of the tracked points are None, ignore
        # them
        if ptsg[p - 1] is None or ptsg[p] is None:
            continue 
	# otherwise, compute the thickness of the line and
	# draw the connecting lines
        thickness = int(np.sqrt(argsg["buffer"] / float(p + 1)) * 5)
        cv2.line(table, ptsg[p - 1], ptsg[p], (255, 0, 0), thickness)

    [i,j] = kick(x,y,i,j)
    #frame=cv2.bitwise_and(frame,frame,mask=mask)
    cv2.circle(table, (int(i),int(j)), 27, (255,0,255), -1)
    # show the frame to our screen
    cv2.imshow("play", table)
    
    if cv2.waitKey(1) == 27:
        break
# cleanup the camera and close any open windows
cap.release()
cv2.destroyAllWindows()
