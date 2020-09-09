#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void menu();
void transaction();
void pass();
void buying();
void selling();
void showDetails();
void detailsShow();
int num, i, SN;
FILE *fp1, *fp2, *fp3;

struct veg //creating a structure to store the details
{
	int SN;
	char name[20];
	float quantity, rate;
} v[100], vs[100], temp[100], temp2[100]; //Creating an structure to use multiple data types

void delay(int mseconds) //for the loader to load
{
	clock_t goal = mseconds + clock();
	while (goal > clock())
		;
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	//guiding gui to work like cui like on turbo C
}

void drawBorder(int a, int b, int length, int height)
{
	gotoxy(a, b); //goes to the co-ordinate provided
	int i, temp;  //temp created to increase the value of b temporarily
	for (i = 0; i < length; i++)
	{
		printf("%c", 219); //prints character 219 along the line horizontally
	}
	temp = b;
	for (i = 1; i < height; i++)
	{
		gotoxy(a, temp++); //prints a character and goes to next line <= on a loop (vertical line)
		printf("%c", 219);
	}
	for (i = 1; i < length; i++)
	{
		printf("%c", 219); //prints character 219 along the line horizontally
	}
	temp = b;
	for (i = 1; i < height; i++)
	{
		gotoxy(a + length, temp++); //goes to the end of length a and prints a charcter and goes to next line <= on a loop
		printf("%c", 219);
	}
}

void main()
{
	system("COLOR 0A"); //changes background color to black (0) and text color to green(A) color codes in the compiler
	int loader;
	system("cls");
	gotoxy(50, 25);
	printf("Developers : Gaida != Rhino");
	gotoxy(50, 15);
	printf("LOADING ");
	for (loader = 1; loader < 20; loader++)
	{
		delay(50);
		printf("%c", 219);
	}
	menu();
}

void menu()
{

	system("cls"); //Menu of the program

	char menu1;

	drawBorder(5, 3, 100, 24); //drwas border around the edge

	gotoxy(41, 6);
	printf("WELCOME TO VEGGIE AID 180");

	gotoxy(30, 9);
	printf("1.Transaction\t\t2.View\t\t3.Exit");

	gotoxy(42, 24);
	time_t currentTime;
	time(&currentTime);
	printf("%s\n", ctime(&currentTime));

	menu1 = getch();

	switch (menu1)
	{
	case '1':
		system("cls");
		transaction();
		break;

	case '2':
		system("cls");
		showDetails();
		break;

	case '3':

		system("cls");
		drawBorder(5, 3, 100, 24);
		gotoxy(40, 13);
		printf("Press Y to exit and N to go back!");
		char character;
		character = getch();
		if (character == 'y' || character == 'Y')
		{
			gotoxy(40, 30);
			system("exit");
			break;
		}

		else
			menu();
		break;
		break;
	}
}

void searchdata()
{
	system("CLS");
	int i = 1, j;
	FILE *buyingit;
	drawBorder(5, 3, 100, 60);
	gotoxy(0, 0);
	gotoxy(45, 5);
	printf("What are you searching for?\n");
	buyingit = fopen("buyingdata.txt", "r");
	while (!feof(buyingit))
	{
		fscanf(buyingit, "%s %f %f\n", &temp[i].name, &temp[i].quantity, &temp[i].rate);
		i++;
	}
	char value[20];
	float total_quantity = 0, total_rate = 0;
	gotoxy(55, 7);
	scanf("%s", value);
	gotoxy(50, 9);
	printf("In buying section:\n\n\t\t\t\tItem:\t\tQuantity\t\tRate\n");
	//int aa = 40;
	//int bb = 20;
	//gotoxy(aa,bb);
	for (j = 1; j < i; j++)
	{
		if ((strcmp(temp[j].name, value) == 0))
		{
			//		gotoxy(aa,bb);
			total_quantity = total_quantity + temp[j].quantity;
			total_rate = total_rate + temp[j].rate;
			printf("\t\t\t\t%s\t\t%f\t\t%f\n", temp[j].name, temp[j].quantity, temp[j].rate);
			//	    aa+=2;
		}
	}
	printf("\n\n\t Total quantity : %.2f\n\t Total rate: %.2f\n\t Total cost: %.2f", total_quantity, total_rate, (total_quantity * total_rate));
	fclose(buyingit);

	FILE *sellingit;
	i = 1;
	sellingit = fopen("sellingdata.txt", "r");
	while (!feof(sellingit))
	{
		fscanf(sellingit, "%s %f %f\n", &temp[i].name, &temp[i].quantity, &temp[i].rate);
		i++;
	}
	float total_quantityy = 0;
	float total_ratee = 0;
	gotoxy(50, 19);

	printf("\n\t-----------------------------------------------------------------------------------------------\n\n\t\t\t\t\t\t In selling section:\n\n\t\t\t\tItem:\t\tQuantity\t\tRate\n");

	for (j = 1; j < i; j++)
	{
		if ((strcmp(temp[j].name, value) == 0))
		{
			total_quantityy = total_quantityy + temp[j].quantity;
			total_ratee = total_ratee + temp[j].rate;
			printf("\t\t\t\t%s\t\t%f\t\t%f\n", temp[j].name, temp[j].quantity, temp[j].rate);
		}
	}
	printf("\n\n\t Total quantity : %.2f\n\t Total rate: %.2f\n\t Total cost: %.2f", total_quantityy, total_ratee, (total_quantityy * total_ratee));
	fclose(sellingit);

	float selling_price = (total_quantityy * total_ratee);
	float buying_price = (total_quantity * total_rate);
	float profit = selling_price - buying_price;
	float loss = buying_price - selling_price;
	if (selling_price > buying_price)
		printf("\n\n\t\t\t\t\tPROFIT by %.2f rupees.", profit);
	else
		printf("\n\n\t\t\t\t\tLOSS by %.2f rupees.", loss);
	getch();
	menu();
}

void deletedata()
{
	int aa = 11, bb = 5;
	system("CLS");
	drawBorder(5, 3, 100, 24);
	gotoxy(aa, bb);
	int i = 1, j;
	FILE *deleteit;
	printf("1. Buying section or 2. selling section ? \n");
	int choice;
	choice = getch();
	if (choice == '1')
	{
		system("CLS");
		drawBorder(5, 3, 100, 60);
		gotoxy(45, 1);
		deleteit = fopen("buyingdata.txt", "r");

		printf("The buying datas are: \n");
		while (!feof(deleteit))
		{
			fscanf(deleteit, "%s %f %f\n", &temp2[i].name, &temp2[i].quantity, &temp2[i].rate);
			i++;
		}
		for (j = 1; j < i; j++)
		{
			bb += 2;
			gotoxy(aa, bb);
			printf("%d.%s %.2f %.2f\n", j, temp2[j].name, temp2[j].quantity, temp2[j].rate);
		}
		fclose(deleteit);
		deleteit = fopen("buyingdata.txt", "w");
		gotoxy(80, 5);
		printf("\n\t\t\t\t\t\t\t\t  Which index do you want to delete?\n");
		int del;
		gotoxy(80, 8);
		scanf("%d", &del);
		for (j = 1; j < i; j++)
		{
			if (j == del)
			{
				continue;
			}
			fprintf(deleteit, "%s %.2f %.2f\n", temp2[j].name, temp2[j].quantity, temp2[j].rate);
		}
		gotoxy(77, 13);
		printf("Deleted!");
		fclose(fp1);
		fclose(deleteit);
		getch();
		menu();
	}
	else if (choice == '2')
	{
		system("CLS");
		drawBorder(5, 3, 100, 60);
		gotoxy(45, 1);
		deleteit = fopen("sellingdata.txt", "r");
		printf("The selling datas are: \n");
		while (!feof(deleteit))
		{
			fscanf(deleteit, "%s %f %f\n", &temp2[i].name, &temp2[i].quantity, &temp2[i].rate);
			i++;
		}
		for (j = 1; j < i; j++)
		{
			bb += 2;
			gotoxy(aa, bb);
			printf("%d.%s %.2f %.2f\n", j, temp2[j].name, temp2[j].quantity, temp2[j].rate);
		}
		fclose(deleteit);
		deleteit = fopen("sellingdata.txt", "w");
		gotoxy(80, 5);
		printf("\n\t\t\t\t\t\t\t\t  Which index do you want to delete?\n");
		int del;
		gotoxy(80, 8);
		scanf("%d", &del);
		for (j = 1; j < i; j++)
		{
			if (j == del)
			{
				continue;
			}
			fprintf(deleteit, "%s %.2f %.2f\n", temp2[j].name, temp2[j].quantity, temp2[j].rate);
		}
		gotoxy(77, 13);
		printf("Deleted!");
		fclose(fp1);
		fclose(deleteit);
		getch();
		menu();
	}
}

void updatedata()
{
	int aa = 11, bb = 5;
	system("CLS");
	drawBorder(5, 3, 100, 24);
	gotoxy(aa, bb);
	int i = 1, j;
	FILE *updateit;
	printf("1. Buying section or 2. selling section ? \n");
	int choice;
	choice = getch();
	if (choice == '1')
	{
		system("CLS");
		drawBorder(5, 1, 100, 60);
		gotoxy(0, 0);
		updateit = fopen("buyingdata.txt", "r");

		while (!feof(updateit))
		{
			fscanf(updateit, "%s %f %f\n", &temp[i].name, &temp[i].quantity, &temp[i].rate);
			i++;
		}
		for (j = 1; j < i; j++)
		{
			bb += 2;
			gotoxy(aa, bb);
			printf("%d.%s %.2f %.2f\n", j, temp[j].name, temp[j].quantity, temp[j].rate);
		}
		fclose(updateit);
		updateit = fopen("buyingdata.txt", "w");
		gotoxy(80, 5);
		printf("\n\t\t\t\t\t\t\t\t  Which index do you want to update?\n");
		int upd;
		gotoxy(80, 8);
		scanf("%d", &upd);
		for (j = 1; j < i; j++)
		{
			if (j == upd)
			{
				float newqty, newrate;
				printf("\n\t\t\t\t\t\t\t\t\tEnter new quantity :\n");
				gotoxy(80, 12);
				scanf("%f", &newqty);

				printf("\n\t\t\t\t\t\t\t\t\t  Enter new rate : \n");
				gotoxy(80, 16);
				scanf("%f", &newrate);
				temp[j].quantity = newqty;
				temp[j].rate = newrate;
				//			printf("%s %f %f\n",temp[j].name,newqty,newrate);
			}
			fprintf(updateit, "%s %.2f %.2f\n", temp[j].name, temp[j].quantity, temp[j].rate);
		}
		gotoxy(77, 19);
		printf("Updated!");

		fclose(fp1);

		fclose(updateit);
		getch();
		menu();
	}
	else if (choice == '2')
	{
		system("CLS");
		drawBorder(5, 3, 100, 60);
		gotoxy(0, 0);
		updateit = fopen("sellingdata.txt", "r");

		while (!feof(updateit))
		{
			fscanf(updateit, "%s %f %f\n", &temp[i].name, &temp[i].quantity, &temp[i].rate);
			i++;
		}
		for (j = 1; j < i; j++)
		{
			bb += 2;
			gotoxy(aa, bb);
			printf("%d.%s %.2f %.2f\n", j, temp[j].name, temp[j].quantity, temp[j].rate);
		}
		fclose(updateit);
		updateit = fopen("sellingdata.txt", "w");
		gotoxy(80, 5);
		printf("\n\t\t\t\t\t\t\t\t  Which index do you want to update?\n");
		int upd;
		gotoxy(80, 8);
		scanf("%d", &upd);
		for (j = 1; j < i; j++)
		{
			if (j == upd)
			{
				float newqty, newrate;
				printf("\n\t\t\t\t\t\t\t\t\tEnter new quantity :\n");
				gotoxy(80, 12);
				scanf("%f", &newqty);

				printf("\n\t\t\t\t\t\t\t\t\t  Enter new rate : \n");
				gotoxy(80, 16);
				scanf("%f", &newrate);
				temp[j].quantity = newqty;
				temp[j].rate = newrate;
			}
			fprintf(updateit, "%s %.2f %.2f\n", temp[j].name, temp[j].quantity, temp[j].rate);
		}
		gotoxy(77, 19);
		printf("Updated!");

		fclose(fp1);

		fclose(updateit);
		getch();
		menu();
	}
}

void profit_loss_data()
{
	system("CLS");
	drawBorder(5, 3, 100, 60);
	gotoxy(0, 0);
	int i = 1, j;
	FILE *profiting_or_losing_it;
	profiting_or_losing_it = fopen("buyingdata.txt", "r");
	if (profiting_or_losing_it == NULL)
	{
		gotoxy(20, 5);
		printf("Something went wrong :( ");
		getch();
		menu();
	}
	while (!feof(profiting_or_losing_it))
	{
		fscanf(profiting_or_losing_it, "%s %f %f\n", &temp[i].name, &temp[i].quantity, &temp[i].rate);
		i++;
	}

	float total_quantity = 0, total_rate = 0;

	gotoxy(45, 5);
	printf("In buying section:\n\n\t\t\t\tItem:\t\tQuantity\tRate\n");
	for (j = 1; j < i; j++)
	{

		total_quantity = total_quantity + temp[j].quantity;
		total_rate = total_rate + temp[j].rate;
		printf("\t\t\t\t%s\t\t%.2f\t\t%.2f\n", temp[j].name, temp[j].quantity, temp[j].rate);
	}
	printf("\n\n\t Total quantity : %.2f\n\n\t Total rate: %.2f\n\n\t Total cost: %.2f", total_quantity, total_rate, (total_quantity * total_rate));
	fclose(profiting_or_losing_it);

	FILE *profiting_or_losing_itt;
	i = 1;
	profiting_or_losing_itt = fopen("sellingdata.txt", "r");
	while (!feof(profiting_or_losing_itt))
	{
		fscanf(profiting_or_losing_itt, "%s %f %f\n", &temp[i].name, &temp[i].quantity, &temp[i].rate);
		i++;
	}
	float total_quantityy = 0;
	float total_ratee = 0;

	printf("\n\t--------------------------------------------------------------------------------------------\n\t\t\t\t\t\tIn selling section:\n\n\t\t\t\tItem:\t\tQuantity\tRate\n");
	for (j = 1; j < i; j++)
	{

		total_quantityy = total_quantityy + temp[j].quantity;
		total_ratee = total_ratee + temp[j].rate;
		printf("\t\t\t\t%s\t\t%.2f\t\t%.2f\n", temp[j].name, temp[j].quantity, temp[j].rate);
	}
	printf("\n\n\t Total quantity : %.2f\n\n\t Total rate: %.2f\n\n\t Total cost: %.2f", total_quantityy, total_ratee, (total_quantityy * total_ratee));
	fclose(profiting_or_losing_itt);

	float selling_price = (total_quantityy * total_ratee);
	float buying_price = (total_quantity * total_rate);
	float profit = selling_price - buying_price;
	float loss = buying_price - selling_price;
	if (selling_price > buying_price)
		printf("\n\t\t\t\t\tPROFIT by %.2f rupees.", profit);
	else
		printf("\n\n\t\t\t\t\tLOSS by %.2f rupees.", loss);
	gotoxy(0, 0);
}

void buyingdet()
{
	int xxx = 8;
	int yyy = 11;
	system("cls");
	drawBorder(5, 3, 100, 60);
	gotoxy(0, 0);
	gotoxy(11, 5);
	printf("Buying details :");
	gotoxy(yyy, xxx);

	fp1 = fopen("buyingdata.txt", "r");
	if (fp1 == NULL)
	{
		printf("Something went wrong :( )");
		getch();
		menu();
	}

	do
	{
		char c = fgetc(fp1);
		if (c == '\n')
		{
			printf("\n");
			xxx += 2;
			gotoxy(yyy, xxx);
		}
		if (feof(fp1))
			break;

		if (c != '\n')
			printf("%c", c);
	} while (1);
	fclose(fp1);
	gotoxy(30, 15);
	printf("\t\t\tPress any key to continue");
}

void sellingdet()
{
	int xx = 8;
	int yy = 11;
	system("cls");
	drawBorder(5, 3, 100, 60);
	gotoxy(0, 0);
	gotoxy(11, 5);
	printf("Selling details :");
	gotoxy(yy, xx);
	fp3 = fopen("sellingdata.txt", "r");
	if (fp3 == NULL)
	{
		printf("Something went wrong :( ");
		getch();
		menu();
	}
	do
	{
		char c = fgetc(fp3);
		if (c == '\n')
		{
			printf("\n");
			xx += 2;
			gotoxy(yy, xx);
		}
		if (feof(fp3))
			break;

		if (c != '\n')
			printf("%c", c);
	} while (1);
	fclose(fp3);
	gotoxy(30, 15);
	printf("\t\t\tPress any key to continue");
}

void alldet()
{
	int xxx = 8;
	int yyy = 11;
	system("cls");
	drawBorder(5, 3, 100, 60);
	gotoxy(0, 0);
	gotoxy(11, 5);
	printf("Buying details :");
	gotoxy(yyy, xxx);

	fp1 = fopen("buyingdata.txt", "r");
	if (fp1 == NULL)
	{
		printf("Something went wrong :( ");
		getch();
		menu();
	}

	do
	{
		char c = fgetc(fp1);
		if (c == '\n')
		{
			printf("\n");
			xxx += 2;
			gotoxy(yyy, xxx);
		}
		if (feof(fp1))
			break;

		if (c != '\n')
			printf("%c", c);
	} while (1);
	fclose(fp1);
	getch();

	int xx = 8;
	int yy = 11;
	system("cls");
	drawBorder(5, 3, 100, 60);
	gotoxy(0, 0);
	gotoxy(11, 5);
	printf("Selling details :");
	gotoxy(yy, xx);

	fp3 = fopen("sellingdata.txt", "r");

	do
	{
		char c = fgetc(fp3);
		if (c == '\n')
		{
			printf("\n");
			xx += 2;
			gotoxy(yy, xx);
		}
		if (feof(fp3))
			break;

		if (c != '\n')
			printf("%c", c);
	} while (1);
	fclose(fp3);
}

void transaction()
{
	system("cls");
	char subMenu;

	drawBorder(5, 3, 100, 24);

	gotoxy(25, 6);
	printf("*********** WELCOME TO TRANSACTION SECTION ***********");

	gotoxy(45, 20);
	printf("Choose any option :) ");

	gotoxy(20, 11);
	printf("1.Buying \t2.Selling\t3.Update\t4.Delete\t5.Search    6.Back");

	subMenu = getch();

	switch (subMenu)
	{
	case '1':
		pass();
		break;

	case '2':
		selling();
		break;

	case '3':
		updatedata();
		break;

	case '4':
		deletedata();
		break;

	case '5':
		searchdata();
		break;

	case '6':
		menu();
		break;
	}
}

void pass()
{
	{

		system("cls");
		char ps[18];
		char password[25], temp;
		char correctpass[10] = "gaida"; //While running the program, type 1 if the program asks

	label:
		drawBorder(5, 3, 100, 24);
		gotoxy(40, 12);
		int f = 0;
		printf("Enter the password : ");

		while (1)
		{
			temp = getch();
			if (temp == 13)
				break;
			else if (f < 0)
			{
				printf("%d", f);
			}
			else if (temp == 8 && f)
			{
				printf("\b");
				printf(" ");
				printf("\b");
				f--;
			}
			else
			{
				password[f] = temp;
				printf("*");
				f++;
			}
		}

		password[f] = '\0';

		if ((strcmp(correctpass, password) == 0))
		{

			buying();
		}

		else
		{
			int repass;
			system("cls");
			drawBorder(5, 3, 100, 24);
			gotoxy(40, 12);
			printf("Password Incorrect!!!");
			gotoxy(40, 15);
			printf("Press any key to re-enter the password.\n\t\t\t\t\tPress 'b' to go back...");
			repass = getch();
			if (repass == 'b')
			{
				transaction();
			}
			else
			{
				system("cls");
				goto label;
			}
		}
	}
}

void pass2()
{
	{

		system("cls");
		char ps[18];
		char password[25], temp;
		char correctpass[10] = "gaida"; //While running the program, type 1 if the program asks

	label:
		drawBorder(5, 3, 100, 24);
		gotoxy(40, 12);
		int f = 0;
		printf("Enter the password : ");

		while (1)
		{
			temp = getch();
			if (temp == 13)
				break;
			else if (f < 0)
			{
				printf("%d", f);
			}
			else if (temp == 8 && f)
			{
				printf("\b");
				printf(" ");
				printf("\b");
				f--;
			}
			else
			{
				password[f] = temp;
				printf("*");
				f++;
			}
		}

		password[f] = '\0';

		if ((strcmp(correctpass, password) == 0))
		{
			detailsShow();
		}

		else
		{
			int repass;
			system("cls");
			drawBorder(5, 3, 100, 24);
			gotoxy(40, 12);
			printf("Password Incorrect!!!");
			gotoxy(40, 15);
			printf("Press any key to re-enter the password.\n\t\t\t\t\tPress 'b' to go back...");
			repass = getch();
			if (repass == 'b')
			{
				menu();
			}
			else
			{
				system("cls");
				goto label;
			}
		}
	}
}

void buying()
{
	int ssubMenu, SN;
	system("cls");
	drawBorder(5, 3, 100, 24);
	gotoxy(30, 5);
	printf("1.Enter the details\t\t2.Back");
	ssubMenu = getch();
	switch (ssubMenu)
	{

	case '1':
		system("cls");
		drawBorder(5, 1, 100, 60);
		gotoxy(0, 0);
		gotoxy(30, 3);
		printf("Enter the number of vegetables bought : ");
		scanf("%d", &num);
		fp1 = fopen("buyingdata.txt", "a"); //main data base for the vegetables bought by the keeper
		for (i = 1; i <= num; i++)			//this creates a loop of this block of code until the given condition matches
		{
			printf("\n\tS.N. %d", i);
			printf("\n\n\tName     :    ");
			scanf(" %s", &v[i].name);
			printf("\tQuantity :    ");
			scanf(" %f", &v[i].quantity);
			printf("\tRate     :    ");
			scanf(" %f", &v[i].rate);
			fprintf(fp1, "%s %0.2f %0.2f\n", v[i].name, v[i].quantity, v[i].rate); //this gets saved in the buyingdata.txt
		}
		printf("\n\tSaved!");
		getch();
		fclose(fp1);
		menu();

	case '2':
	{
		system("cls");
		transaction();
		break;
	}
	}
}

void selling()
{
	int sellings, soldnum;
	system("cls");
	drawBorder(5, 3, 100, 24);
	gotoxy(30, 5);
	printf("1.Enter the details\t\t2.Back");
	sellings = getch();
	switch (sellings)
	{

	case '1':

		system("cls");
		drawBorder(5, 1, 100, 60);
		gotoxy(0, 0);
		gotoxy(30, 3);
		printf("Enter the number of vegetables sold : ");
		scanf("%d", &soldnum);
		fp1 = fopen("sellingdata.txt", "a"); //main data base for the vegetables bought by the keeper
		for (i = 1; i <= soldnum; i++)		 //this creates a loop of this block of code until the given condition matches
		{
			printf("\n\tS.N. %d", i);
			printf("\n\n\tName     :    ");
			scanf(" %s", &v[i].name);
			printf("\tQuantity :    ");
			scanf(" %f", &v[i].quantity);
			printf("\tRate     :    ");
			scanf(" %f", &v[i].rate);
			fprintf(fp1, "%s %0.2f %0.2f\n", v[i].name, v[i].quantity, v[i].rate); //this gets saved in the buyingdata.txt
		}
		printf("\n\tSaved!");
		getch();
		fclose(fp1);
		menu();

	case '2':
	{

		system("cls");
		transaction();
		break;
	}
	}
}

void detailsShow()
{
	system("CLS");
	drawBorder(5, 3, 100, 24);
	gotoxy(41, 6);
	char vs;
	printf("What do you want to view?\n\n\n");
	printf("\t\t 1. Buying Details\n\n\t\t 2. Selling Details\n\n\t\t 3. Complete Details\n\n\t\t 4. Profit/Loss\n\n\t\t 5. Back");
	vs = getch();

	switch (vs)
	{

	case '1':
	{
		buyingdet();
		getch();
		menu();
		break;
	}

	case '2':
	{
		sellingdet();
		getch();
		menu();
		break;
	}

	case '3':
	{
		alldet();
		getch();
		menu();
		break;
	}

	case '4':
	{
		profit_loss_data();
		getch();
		menu();
		break;
	}

	case '5':
	{
		menu();
		break;
	}
	}
}

void showDetails()
{
	system("cls");
	pass2();
}
