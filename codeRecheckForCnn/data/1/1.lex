enum t1{ti_1,ti_2}
 struct db {
 int a, b;
 union db2 {
 double temp1;
 int temp2;
 };
 };
 int a, b;
 void go(int a,int b) {
 for (int i = 1; i <= 10; i++) {
 while (i) {
 switch (i)
 {
 case 1:
 return 1;
 case 2:
 return 2;
 default:
 break;
 }
 }
 if (i < 2)return 2;
 else if (i < 3)return 3;
 else if (i < 4)return 4;
 }
 }
 int add(int a, int b) {
 return a + b;
 }
 int sub (int a, int b) {
 return a - b;
 }
 int mult(int a, int b) {
 return a * b;
 }
 int div1(int a, int b) {
 return (int)(a / b);
 }
 int cal(int oper,int a, int b) {
 switch (oper)
 {
 case 1:
 return add(a, b); break;
 case 2:
 return sub(a, b); break;
 case 3:
 return mult(a, b); break;
 case 4:
 return div1(a, b); break;
 default:
 break;
 }
 }
 int[] go(int a,int b){
 int p[3]={0};
 return p;
 }
 int main() {
 db t1;
 int a, b;
 int a[2];
 double db[3];
 char ch[3];
 char ch32='c';
 a = 20, b = 20;
 double db=34.6;
 printf("%d", cal(1, a/c, (b+c)*a));
 system("pause");
 return 0;
 }
 