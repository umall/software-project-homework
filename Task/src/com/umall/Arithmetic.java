package com.umall;

import java.util.*;
import java.applet.*;
import java.awt.*;

public class Arithmetic extends Applet{
	static int a1,a2,a3;
	static int b1,b2;
	static char c;
	static float sum;
	public static void main(String[] args) {
		System.out.println("请输入出题数量：");
		Scanner in = new Scanner(System.in);
		int count = in.nextInt();
		int i = 0;
		int j = 0;
		float[] sums = new float[count];
		while(i < count) {
			getRandom1();
			getRandom2();
//			System.out.println(a1);
//			System.out.println(a2);
//			System.out.println(a3);
//			System.out.println(b1);
//			System.out.println(b2);
			char c1 = Judger(b1);
			char c2 = Judger(b2);
//			System.out.println(c1);
//			System.out.println(c2);
			Compute(c1,c2);
			sums[i] = sum;
//			System.out.println(sum);  
			if(sum >= 0 && sum <= 100) {
				System.out.printf("%2d    %2d %c %2d %c %2d = \n",i + 1,a1,c1,a2,c2,a3);
				i++;
			}
//			if(sum >= 0 && sum <= 100) {
//				System.out.printf("%.2f\n",sum);
//				j++;
//			}
		}
		System.out.println();
		System.out.println("是否输出答案（Y/y--其他）");
		String sc = in.next();
		char s = sc.charAt(0);
		int k;
		if(s == 'Y' || s == 'y') {
			for(k = 0;k < count; k++ ) {
				System.out.printf("%2d    %.2f\n",k + 1,sums[k]);
			}
		}
		else {
			System.out.println("over!");
		}
	}
	
	//随机生成三个操作数
	public static void getRandom1() {
		Random r = new Random();
		a1 = r.nextInt(100);
		a2 = r.nextInt(100);
		a3 = r.nextInt(100);
	}
	
	//随机生成两个数
	public static void getRandom2() { 
		Random r = new Random();
		b1 = r.nextInt(100);
		b2 = r.nextInt(100);
	}
	
	//判断一个数是什么运算符号
	public static char Judger(int a) {
		char c;
		if(a >= 0 && a <= 24) {
			c = '+';
		}
		else if(a >= 25 && a <= 49) {
			c = '-';
		}
		else if(a >= 50 && a <= 74) {
			c = '×';
		}
		else {
			c = '÷';
		}
		return c;
	}
	
	//对于不同的运算符   给出不同的计算方式
	public static float Switch(char c,float a,float b) {
		switch (c) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '×':
			return a * b;
		case '÷':
			return (float)a / b;	
		default:
			return 0;
		}
	}
	
	//给定两个运算符  有前后的运算规则
	public static void Compute(char c1,char c2) {
		if(c1 == '×' || c1 == '÷') {
			sum = Switch(c1,a1,a2);
			sum = Switch(c2,sum,a3);
		}
		if(c1 == '+' || c1 == '-') {
			if(c2 == '×' || c2 == '÷') {
				sum = Switch(c2,a2,a3);
				sum = Switch(c1,sum,a1);
			}
			else {
				sum = Switch(c1,a1,a2);
				sum = Switch(c2,sum,a3);
			}
		}
	}
	
}

