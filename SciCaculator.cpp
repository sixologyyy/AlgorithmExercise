/*---------------------------------------
�����ͼ�����(VC++6.0,Win32 Console)������ yu_hua ��2007-07-27������
���ܣ�
Ŀǰ�ṩ��10���������ѧ����:
������sin
������cos
������tan
�ȿ�ƽ��sqrt
�ɷ�����arcsin
�ʷ�����arccos
�˷�����arctan
�̳��ö���lg
����Ȼ����ln
�Σ�ָ��exp
�ϳ��ݺ�����
�÷���
���Ҫ��2��32���ݣ����Դ���2^32<�س�>
���Ҫ��30�Ƚǵ����пɼ���tan(Pi/6)<�س�>
ע�ⲻ�ܴ��룺tan(30)<Enter>
���Ҫ��1.23���ȵ����ң��м��ַ�������Ч��
sin(1.23)<Enter>
sin 1.23 <Enter>
sin1.23  <Enter>
�����֤�����ҵ�ƽ���͹�ʽ,�ɴ���sin(1.23)^2+cos(1.23)^2 <Enter>��sin1.23^2+cos1.23^2 <Enter>
�������������ʽ����һ��,�Զ����Ϊ����磺sin1.23cos0.77+cos1.23sin0.77�͵ȼ���sin(1.23)*cos(0.77)+cos(1.23)*sin(0.77)
��Ȼ�㻹�����������Ǳ任������sin(1.23+0.77)Ҳ��sin2��֤һ�¡�
����������ֿ���������������ȼ�������磺2+3*4^2 ʵ�����൱�ڣ�2+(3*(4*4))
���⺯����ǰ�����������,��ô�Զ���Ϊ�������.
ͬ�����ĳ�����Ҳ��������ţ����Զ���Ϊ������������֮������һ�˺š�
�磺3sin1.2^2+5cos2.1^2 �൱��3*sin2(1.2)+5*cos2(2.1)
���磺4(3-2(sqrt5-1)+ln2)+lg5 �൱��4*(3-2*(��5 -1)+loge(2))+log10(5)
���⣬���������ṩ��Բ���� Pi������ĸʱ�����ִ�Сд,�Է���ʹ�á�
----------------------------------------*/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <windows.h>
using namespace std;
const char Tab = 0x9;
const int  DIGIT = 1;
const int MAXLEN = 16384;
char s[MAXLEN], *endss;
int pcs = 15;
double fun(double x, char op[], int *iop) {
	while (op[*iop - 1]<32) //����ʹ�ú���Ƕ�׵���ʱ���ؼ�����,�� arc sin(sin(1.234)) ֻ�����arc sin sin 1.234<Enter>
		switch (op[*iop - 1]) {
		case  7: x = sin(x);  (*iop)--; break;
		case  8: x = cos(x);  (*iop)--; break;
		case  9: x = tan(x);  (*iop)--; break;
		case 10: x = sqrt(x); (*iop)--; break;
		case 11: x = asin(x); (*iop)--; break;
		case 12: x = acos(x); (*iop)--; break;
		case 13: x = atan(x); (*iop)--; break;
		case 14: x = log10(x); (*iop)--; break;
		case 15: x = log(x);  (*iop)--; break;
		case 16: x = exp(x);  (*iop)--; break;
	}
	return x;
}
double calc(char *expr, char **addr) {
	static int deep; //�ݹ����
	static char *fname[] = { "sin", "cos", "tan", "sqrt", "arcsin", "arccos", "arctan", "lg", "ln", "exp", NULL };
	double ST[10] = { 0.0 }; //����ջ
	char op[10] = { '+' }; //�����ջ
	char c, *rexp, *pp, *pf;
	int ist = 1, iop = 1, last;
	if (!deep) {
		pp = pf = expr;
		do {
			c = *pp++;
			if (c != ' '&& c != Tab)
				*pf++ = c;
		} while (c != '\0');
	}
	pp = expr;
	if ((c = *pp) == '-' || c == '+') {
		op[0] = c;
		pp++;
	}
	last = !DIGIT;
	while ((c = *pp) != '\0') {
		if (c == '(') {//��Բ����
			deep++;
			ST[ist++] = calc(++pp, addr);
			deep--;
			ST[ist - 1] = fun(ST[ist - 1], op, &iop);
			pp = *addr;
			last = DIGIT;
			if (*pp == '(' || isalpha(*pp) && _strnicmp(pp, "Pi", 2)) {//Ŀ���ǣ�����Բ����������Ϊ��Բ������������ʱ��Ĭ����Ϊ�˷�
				op[iop++] = '*';
				last = !DIGIT;
				c = op[--iop];
				goto operate;
			}
		}
		else if (c == ')') {//��Բ����
			pp++;
			break;
		}
		else if (isalpha(c)) {
			if (!_strnicmp(pp, "Pi", 2)) {
				if (last == DIGIT) {
					cout << "���������" << endl; exit(1);
				}
				ST[ist++] = 3.14159265358979323846264338328;
				ST[ist - 1] = fun(ST[ist - 1], op, &iop);
				pp += 2;
				last = DIGIT;
				if (!_strnicmp(pp, "Pi", 2)) {
					cout << "����������" << endl; exit(2);
				}
				if (*pp == '(') {
					cout << "���Ҳ�����" << endl; exit(3);
				}
			}
			else {
				int i;
				for (i = 0; (pf = fname[i]) != NULL; i++)
				if (!_strnicmp(pp, pf, strlen(pf)))break;
				if (pf != NULL) {
					op[iop++] = 07 + i;
					pp += strlen(pf);
				}
				else {
					cout << "İ��������" << endl; exit(4);
				}
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
			char cc;
			if (last != DIGIT) {
				cout << "�����ճ��" << endl; exit(5);
			}
			pp++;
			if (c == '+' || c == '-') {
				do {
					cc = op[--iop];
					--ist;
					switch (cc) {
					case '+':  ST[ist - 1] += ST[ist]; break;
					case '-':  ST[ist - 1] -= ST[ist]; break;
					case '*':  ST[ist - 1] *= ST[ist]; break;
					case '/':  ST[ist - 1] /= ST[ist]; break;
					case '^':  ST[ist - 1] = pow(ST[ist - 1], ST[ist]); break;
					}
				} while (iop);
				op[iop++] = c;
			}
			else if (c == '*' || c == '/') {
			operate:        cc = op[iop - 1];
				if (cc == '+' || cc == '-') {
					op[iop++] = c;
				}
				else {
					--ist;
					op[iop - 1] = c;
					switch (cc) {
					case '*':  ST[ist - 1] *= ST[ist]; break;
					case '/':  ST[ist - 1] /= ST[ist]; break;
					case '^':  ST[ist - 1] = pow(ST[ist - 1], ST[ist]); break;
					}
				}
			}
			else {
				cc = op[iop - 1];
				if (cc == '^') {
					cout << "���ݷ�����" << endl; exit(6);
				}
				op[iop++] = c;
			}
			last = !DIGIT;
		}
		else {
			if (last == DIGIT) {
				cout << "������ճ��" << endl; exit(7);
			}
			ST[ist++] = strtod(pp, &rexp);
			ST[ist - 1] = fun(ST[ist - 1], op, &iop);
			if (pp == rexp) {
				cout << "�Ƿ��ַ�" << endl; exit(8);
			}
			pp = rexp;
			last = DIGIT;
			if (*pp == '(' || isalpha(*pp)) {
				op[iop++] = '*';
				last = !DIGIT;
				c = op[--iop];
				goto operate;
			}
		}
	}
	*addr = pp;
	if (iop >= ist) {
		cout << "���ʽ����" << endl; exit(9);
	}
	while (iop) {
		--ist;
		switch (op[--iop]) {
		case '+':  ST[ist - 1] += ST[ist]; break;
		case '-':  ST[ist - 1] -= ST[ist]; break;
		case '*':  ST[ist - 1] *= ST[ist]; break;
		case '/':  ST[ist - 1] /= ST[ist]; break;
		case '^':  ST[ist - 1] = pow(ST[ist - 1], ST[ist]); break;
		}
	}
	return ST[0];
}
int main(int argc, char **argv) {
	if (argc <= 1) {
		if (GetConsoleOutputCP() != 936) system("chcp 936>NUL");//���Ĵ���ҳ
		cout << "���㺯�����ʽ��ֵ��" << endl << "֧��(),+,-,*,/,^,Pi,sin,cos,tan,sqrt,arcsin,arccos,arctan,lg,ln,exp" << endl;
		while (1) {
			cout << "��������ʽ��";
			gets(s);
			if (s[0] == 0) break;//
			cout << s << "=";
			cout << setprecision(15) << calc(s, &endss) << endl;
		}
	}
	else {
		strncpy(s, argv[1], MAXLEN - 1); s[MAXLEN - 1] = 0;
		if (argc >= 3) {
			pcs = atoi(argv[2]);
			if (pcs<0 || 15<pcs) pcs = 15;
			printf("%.*lf\n", pcs, calc(s, &endss));
		}
		else {
			printf("%.15lg\n", calc(s, &endss));
		}
	}
	return 0;
}
