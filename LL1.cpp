#include <stdio.h>
#include <string.h>
#define Max0 6
#define Max1 7
#define Max2 4
#define MAXSIZE 10

typedef struct {
	char base[MAXSIZE];
	int top;
}sqstack;

void InitStack(sqstack& S) {
	S.top = 0;
}

void push(sqstack& S, char e) {
	if (S.top == MAXSIZE)
		return;
	S.base[S.top] = e;
	S.top++;
}

char GetTop(sqstack& S) {
	if (S.top == 0)
		return -1;
	return S.base[S.top--];
}

char Pop(sqstack& S) {
	if (S.top == 0)
		return 0;
	S.top--;
	return S.base[S.top];
}

char AnalyseTable[Max0][Max1][Max2] = {
	{"", "i", "+", "*", "(", ")", "#"},
	{"E", "TA", "", "", "TA", "", ""},
	{"A", "", "+TA", "", "","@","@"},
	{"T", "FB", "", "", "FB","", ""},
	{"B", "", "@", "*FB", "", "@", "@"},
	{"F", "i", "", "", "(E)", "", ""}
};

char str[9] = "";
int ip = 0;

int LineOfStackTop(char ch) {
	for (int i = 1; i < Max0; i++)
		if (AnalyseTable[i][0][0] == ch) {
			return i;
			break;
		}
	return 0;
}

int CoumOfCurrentChar(char ch) {
	for (int i = 0; i < Max1; i++)
		if (AnalyseTable[0][i][0] == ch)
		{
			return i;
			break;
		}
	return 0;
}

void main() {
	printf("请输入字符串（以#结束）：");
	scanf("%s", str);
	sqstack S;
	InitStack(S);
	push(S, '#');
	push(S, 'E');
	int line = 0;
	int colum = 0;

	while (S.top != 0)
	{
		if (GetTop(S) == str[ip] && str[ip] != '#') {
			Pop(S);
			ip++;
		}
		else if((GetTop(S) == str[ip] && str[ip] == '#'))
		{
			printf("匹配成功");
			break;
		}
		else {
			line = LineOfStackTop(Pop(S));
			colum = CoumOfCurrentChar(str[ip]);

			if (strcmp(AnalyseTable[line][colum], "") == 0) {
				printf("匹配失败");
				break;
			}
			else {
				int k = 0;
				while (AnalyseTable[line][colum][k] != 0)
					k++;
				k--;
				while (k >= 0 && AnalyseTable[line][colum][k] != '@')
				{
					push(S, AnalyseTable[line][colum][k] != 0);
					k--;
				}
			}
		}
	}
}




