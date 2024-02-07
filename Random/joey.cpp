#include <bits/stdc++.h>
using namespace std;

int count(string s,char c)
{
    int count=0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] ==  c)
        {
            count++;
        }
    }
    return count;
}
//Approach:Just count the special characters like w in two x in six
int sumOfString(string s)
{
    int zero,one,two,three,four,five,six,seven,eight,nine;
    zero=count(s,'z');
    two=count(s,'w');
    four=count(s,'u');
    five=count(s,'f')-four;
    six=count(s,'x');
    seven=count(s,'s')-six;
    eight=count(s,'g');
    nine=count(s,'i')-five-six-eight;
    one=count(s,'o')-zero-two-four;
    three=count(s,'r')-zero-four;
    
    int sum=one+2*two+3*three+4*four+5*five+6*six+7*seven+8*eight+9*nine;
    return sum;
    
}
int main()
{
    string s;
    cin>>s;
    int ans=sumOfString(s);
    cout<<ans;
    return 0;
}



import cv2

def eye_aspect_ratio(eye):
    A = ((eye[1][0] - eye[5][0]) ** 2 + (eye[1][1] - eye[5][1]) ** 2) ** 0.5
    B = ((eye[2][0] - eye[4][0]) ** 2 + (eye[2][1] - eye[4][1]) ** 2) ** 0.5
    C = ((eye[0][0] - eye[3][0]) ** 2 + (eye[0][1] - eye[3][1]) ** 2) ** 0.5
    ear = (A + B) / (2.0 * C)
    return ear

thresh = 0.25
frame_check = 20

# Load the Haar cascades for face and eye detection
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_eye.xml')

cap = cv2.VideoCapture(0)
flag = 0

while True:
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    for (x, y, w, h) in faces:
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = frame[y:y+h, x:x+w]

        eyes = eye_cascade.detectMultiScale(roi_gray)
        if len(eyes) >= 2:
            # Assume the first two rectangles correspond to the left and right eyes
            left_eye = eyes[0:1]
            right_eye = eyes[1:2]

            leftEAR = eye_aspect_ratio(left_eye)
            rightEAR = eye_aspect_ratio(right_eye)
            ear = (leftEAR + rightEAR) / 2.0

            if ear < thresh:
                flag += 1
                if flag >= frame_check:
                    cv2.putText(frame, "****************ALERT!****************", (10, 30),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
                    cv2.putText(frame, "****************ALERT!****************", (10,325),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
        else:
            flag = 0

    cv2.imshow("Frame", frame)
    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break

cv2.destroyAllWindows()
cap.release()

