 {% include _youtube.html id="https://youtu.be/_nfCblHYu-I" %}

# OpenGL-Lego-Game 😀
　Visual Studio IDE를 이용하고 Opengl 오픈 그래픽 라이브러리를 이용하여 실습하였다. 이 API는 약 250여개 가량의 함수 호출	을 이용하여 단순한 기하도형에서부터 복잡한 삼차원 장면을 생성할 수 있다. OpenGL은 현재 CAD, 가상현실, 정보시각화, 비행 시뮬레이션 등의 분야에서 활용되고 있다. 또한 컴퓨터 게임 분야에서도 널리 활용되고 있으며, 마이크로소프트사의 Direct3D와 함께 컴퓨터 그래픽 세계를 양분하고 있다.
 
프로젝트의 주제는 다음과 같다. "레고를 활용하여 게임을 만들기". 참으로 제한적인 주제이면서 창의성을 요구하는 주제였다. 제작년에도 선배들이 이 주제를 가지고 프로젝트를 한 사례가 있었고 레고로 자동차 만들기, 레고 놀이동산 만들기 등 개인적으로 누구나 생각할 수 있는 주제들이였다. 본인은 이런 한정적인 주제가 별로 마음에 들지 않았지만 창의적인 아이디어를 내기 위해 노력하였다. 내가 생각한 주제는 레고로 탈출 맵을 생성하고 레고 캐릭터가 그위를 이동하면서 탈출하는 주제이다. 


### Discussion 🤕 :
　처음으로 2000줄이 넘는 소스코드를 작성해봤고 이렇게 길게 작성한것도 처음이여서 프로그램이 가동되는 것에만 집중하여 코드가 매우 지저분하다. 사실상 C언어로 짠 것과 다름없는 절차식 코드라고 해도 무방하다. 나중에는 코드가 너무 길어져서 유지 보수와 오류 찾기에 시간낭비를 엄청 하였는데 이것 또한 교훈이 된 과목이였다.

#### Camera

```cpp
void motion(int x, int y) {
	if (drag == 1) { // 좌클릭 Press 상태
		if (gamemode == 0) {
			if (x > tempX) {
				phi = phi + 1;
				if (phi >= 355) {
					phi = 0;
				}
			}
			else if (x < tempX) {
				phi = phi - 1;
				if (phi <= 0) {
					phi = 360;
				}
			}
			if (y > tempY) {
				if (theta < 88)theta = theta + 1;
				if (fmod(theta, 180) == 0.5) { //  지형 밑으로 시점 못내려감.
					upY = -1;
				}
				if (theta >= 360) {
					theta = 5; upY = 1;
				}
			}
			else if (y < tempY) {
				if (theta > 1)theta = theta - 1;
				if (fmod(theta, 180) == 0) {
					upY = 1;
				}
				if (theta <= 0) {
					theta = 360; upY = -1;
				}
			}
			tempX = x;	tempY = y;
		}        
        .....
	}

	eyeX = r * sin(deg2rad(theta))*sin(deg2rad(phi));
	eyeY = r * cos(deg2rad(theta));
	eyeZ = r * sin(deg2rad(theta))*cos(deg2rad(phi));

	.....
	glutPostRedisplay();
}

```


 또한 GLUT는 반복적인 처리가 필요할 때 주로 사용되는 타이머 이벤트도 제공한다.

void glutTimerFunc(unsigned int millis, void (*func)(int value), int value); 
msec 후에 func함수를 호출하며 인수로 value를 전달한다. value는 타이머 콜백으로 전달되어 작업거리를 지시하는데 타이머의 용도가 하나뿐이라면 아무값이나 주어도 상관은 없다. 콜백을 등록해 놓으면 millis 후에 콜백함수가 호출된다. 일반적인 타이머와는 다르게 주기적으로 호출되는게 아니라 딱 한번만 호출된다. 주기적으로 계속 호출하려면 콜백함수에서 자신을 계속 호출해야한다. 불편하긴 하지만, 호출될때마다 다음 주기를 가변적으로 설정할 수 있다는 점에서 활용성은 더 높다.

 +)애니메이션을 할 때에는 더블버퍼링을 사용하는게 좋다.
버퍼 한개에서 지웠다 그렸다를 반복하면 깜빡임 현상이 발생하기 때문이다.
