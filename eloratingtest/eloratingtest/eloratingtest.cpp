#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int id;
	int score;
	int devi;
	int rank;
} Player; // 구조체 정의



void deviation(Player* p) {
	int sum = 0, average;
	for (int i = 0; i < 8; i++) {
		sum += p[i].score;
	}
	average = sum / 8;
	
	for (int i = 0; i < 8; i++) {
		p[i].devi = p[i].score - average;
	}
} // 편차 구하는 함수

void simulModel1 (Player* p, int* s, int rnd) {
	for (int i = 0; i < 8; i++) {
		p[i].rank = i;
	}

	deviation(p);

	for (int i = 0; i < 8; i++) {
		if (s[i] - p[i].devi <= -100) {
			p[i].score -= 100;
		}
		else {
			p[i].score = p[i].score + s[i] - p[i].devi;
		}
	}

	printf("\n\n[ %d회 시행결과 ]\n\n", rnd);

	for (int i = 0; i < 8; i++) {
		printf("%d번 선수: %d점 (편차 : %d)\n", i + 1, p[i].score, p[i].devi);
	}
} // 1등 -> 1등 2등 -> 2등 ...

void shuffleRank(int* r, int size) {
	for (int i = size - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = r[i];
		r[i] = r[j];
		r[j] = temp;
	}
}

void simulModel2(Player* p, int* s, int rnd) {
	int makeRank[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	shuffleRank(makeRank, 8);

	int max = 0, min = 0, difference = 0;

	for (int i = 0; i < 8; i++) {
		p[i].rank = makeRank[i];
	}

	printf("\n\n\n난수 생성 결과: ");
	for (int i = 0; i < 8; i++) {
		printf("%d ", makeRank[i]);
	}

	deviation(p);

	for (int i = 0; i < 8; i++) {
		if (s[p[i].rank] - p[i].devi <= -100) {
			p[i].score -= 100;
		}
		else {
			p[i].score = p[i].score + s[p[i].rank] - p[i].devi;
		}
	}

	printf("\n\n[ %d회 시행결과 ]\n\n", rnd);

	for (int i = 0; i < 8; i++) {
		printf("%d번 선수: %d점 (편차 : %d, 순위 : %d위)\n", i + 1, p[i].score, p[i].devi, p[i].rank + 1);
	}

	for (int i = 0; i < 8; i++) {
		if (p[i].score > max) {
			max = p[i].score;
		}
	}

	min = max;

	for (int i = 0; i < 8; i++) {
		if (p[i].score < min) {
			min = p[i].score;
		}
	}

	difference = max - min;

	printf("\n최대 점수 차: %d\n", difference);
} // 라운드마다 랜덤 순위

int main()
{
	srand(time(NULL));

	printf("WPLoLChessLeague (WCL) Elo Rating Simulation\n");

	int count, startScr, mode, rnd = 1;
	int scr[8] = { 100, 50, 30, 20, -20, -30, -50, -100 };
	Player p[8];
	
	printf("\n\n초기점수를 입력해주세요: ");
	scanf_s("%d", &startScr);

	for (int i = 0; i < 8; i++) {
		p[i].id = i;
		p[i].score = startScr;
	}

	printf("\n\n시뮬레이션 방법을 입력해주세요 (1 : 1등이 1등, 2 : 랜덤): ");
	scanf_s("%d", &mode);

	printf("\n\n시뮬레이션 횟수를 입력해주세요: ");
	scanf_s("%d", &count);

	for (int i = 0; i < count; i++) {
		if (mode == 1) {
			simulModel1(p, scr, rnd);
			rnd++;
		}
		else if (mode == 2) {
			simulModel2(p, scr, rnd);
			rnd++;
		}
	}
}