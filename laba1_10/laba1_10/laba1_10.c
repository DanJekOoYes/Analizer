#include <stdio.h>
#include <locale.h>
#include <string.h>;
#define AMOUNT_FIRMS 10
#define AMOUNT_DEBT 5
#define TRUE 1
#define FALSE 0


typedef struct
{
	char name[31];
	char taxe[8];
	char deadline[11];
	char date_pay[11];
} firm;

//������ ���� ����� name ���������� \0, ��� ������������ ������ ������
void init_firms(firm* firms, int amount);

void add_firm_name(firm** firms, char* name);

void add_firm_taxe(firm* rec, char* taxe);

void add_firm_dates(firm* rec, char* deadline, char* date_pay);

int month_compare(char* month, char* deadline);

//����� ���� ���� � ���������� ��������������� �� ���������� ������ deadline
void five_debt(firm* firms, char* month_of_deadline);

void show_firm(firm* rec);

void add_firm_date_pay(firm* rec, char* datepay);

void copy_firm(firm* dest, firm* src);

void swap_firms(firm* rec1, firm* rec2);

void sort_firms_alhabet(firm* fims);

int main(void)
{
	setlocale(LC_ALL, "Russian");

	printf("Labaroratornaya rabota 1_10(semestr II)\n");

	printf("\n-------------------------------------------\n");
	firm firms[AMOUNT_FIRMS] = 
	{
		//1000,1004,1010,1034,1040,1041,1055,1060,1060
		{ "Town", "1010", "08.07.2014", "08.04.2014" },
		{ "Aow", "1010", "08.03.2014", "08.04.2014" },
		{ "Aawn", "1004", "08.07.2014", "08.04.2014" },
		{ "Town", "1034", "08.07.2014", "08.04.2014" },
		{ "Town", "1040", "08.07.2014", "08.04.2014" },
		{ "Bown", "1060", "08.03.2014", "08.04.2014" },
		{ "Aown", "1060", "08.03.2014", "08.04.2014" },
		{ "Hown", "1055", "08.07.2014", "08.04.2014" },
		{ "Town", "1041", "08.07.2014", "08.04.2014" },
		{ '\0', "1042", "08.03.2014", "smth" }
	};

	five_debt(firms, "03");

	printf("\n\nMonth compare: %d", month_compare("03", "13.03.2014"));

	firm sample;

	printf("\n\n");
	return 0;
}

void init_firms(firm* firms, int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		firms[i].name[0] = '\0';
	}
}

void add_firm_name(firm* firms, char* name)
{
	//������� ������ ������ ������
	int last = 0;
	while (firms[last].name[0] != '\0')
		++last;

	//���������� ���
	strcpy(firms[last].name, name);
}

void add_firm_taxe(firm* rec, char* taxe)
{
	strcpy(rec->taxe, taxe);
}

void add_firm_dates(firm* rec, char* deadline, char* datepay)
{

	strcpy(rec->deadline, deadline);
	strcpy(rec->date_pay, datepay);
}

void show_firm(firm* rec)
{
	printf("\n %-5s|", rec->name);
	printf("\t%-13s|", rec->deadline);
	printf("\t%-6s|", rec->taxe);
	printf("\t%s|\n", rec->date_pay);
	printf("\n-------------------------------------------\n");
}

int month_compare(char* month, char* deadline)
{
	int i = 0;
	while (deadline[i++] != '.');
	for (int j = 0; j < 2; ++j)
	{
		if (month[j] != deadline[i++])
			return FALSE;
	}
	return TRUE;
}

void five_debt(firm* rec, char* month_of_deadline)
{
	int i = 0, j = 0;
	int max, ind;
	int find_rec = FALSE;//���������� TRUE ���� ������ ������� �������������� �������� ������
	int curr_minimas = 0;//���-�� ��������� � ���������� �����

	while (rec[i].name[0] != '\0')
	{
		if (month_compare(month_of_deadline, rec[i].deadline) == 1)
		{
			find_rec = TRUE;
		}
		++i;
	}

	//���� ���� �������
	if (i == 0)
	{
		printf("\n������, ���� ������ �����\n");
		return;
	}
	//���� ���� ����������� ������
	else if (find_rec == FALSE)
	{
		printf("\n���� ���������� �������\n");
		return;
	}
	//���� ���� ���� ���� ������ - ������ ��������� �������
	else
	{
		printf("\n Name |\tDeadline     |\tTaxe  |\tDate_pay  |\n");
		printf("\n-------------------------------------------\n");
		max = atoi(rec[0].taxe);
		ind = 0;
	}
	
	//��������� � ������ ������� ������������ ������������� � ���������� �����
	//curr_minimas - ������� �� �������� ���-��
	while (rec[j].name[0] != '\0' && curr_minimas < AMOUNT_DEBT)
	{
		//�������� (curr_minimas - 1) �� �����, �.�. ��� ����� ���������� ��������, � ������������ ������ � ���������� �� ������
		i = curr_minimas;
		while (rec[i].name[0] != '\0')
		{
			if ((max < atoi(rec[i].taxe)) && (month_compare(month_of_deadline, rec[i].deadline) == TRUE))
			{
				max = atoi(rec[i].taxe);
				ind = i;
				find_rec = TRUE;
			}
			++i;
		}
		if (find_rec == TRUE)
		{
			swap_firms(&rec[ind], &rec[curr_minimas++]);
			find_rec = FALSE;
		}
		++j;
		max = atoi(rec[i].taxe);
	}
	//������ � ������ curr_minimas ��������� ����� ������������ �����, ���������� ������ curr_minimas ���������
	int k = 0;
	for (int i = 0; i < curr_minimas; ++i)
	{
		
		for (int j = i; j < curr_minimas; ++j)
		{
			//���� ������ ����� ��������� � ��������� ��������
			if (strcmp(rec[i].name, rec[j].name) == 0)
			{
				continue;
			}

			k = 0;
			//����������� ���������� ��������
			while (rec[i].name[k] == rec[j].name[k])
			{
				++k;
			}

			//���� ������ ������, �� � ��������� ������
			if ((rec[i].name[k] > rec[j].name[k])||(rec[j].name[k]=='\0'))
			{
				swap_firms(&rec[i], &rec[j]);
			}
		}
	}
	//������� ������ ���� ���������
	for (int i = 0; i < curr_minimas; ++i)
	{
		show_firm(&rec[i]);
	}
}

void copy_firm(firm* dest, firm* src)
{
	strcpy(dest->name, src->name);
	strcpy(dest->taxe, src->taxe);
	strcpy(dest->deadline, src->deadline);
	strcpy(dest->date_pay, src->date_pay);

}

void swap_firms(firm* rec1, firm* rec2)
{
	firm temp;
	copy_firm(&temp, rec1);
	copy_firm(rec1, rec2);
	copy_firm(rec2, &temp);
}


//!--��������
/*//�.�. old_max ��� ������� ������� - ���� ������� ������
//(������ ���-�� ��� �� ������� ���� ���-�� �������) 4 ���� ������ ���� ������ � ������� ���������� ������
while (rec[i].name[0] != '\0' && i < AMOUNT_DEBT - 1)
{
	//�.�. ������ ������� = ��� ��, ������� ��� �����
	j = curr_minimas;
	//������ �� �������
	while (rec[j].name[0] != '\0')
	{
		//���� 
		//�������_���� ������ �������� ��������, � ������� ������� ������ �������_����  
		//���
		//������� ������ ������ ������� ������_���� � ������� ������� ����� �������_����
		//�
		//��� ��������� ����� ��������
		if (
			((atoi(rec[j].taxe) > curr_max && atoi(rec[j].taxe) < old_max)
			&&
			(month_compare(month_of_deadline, rec[i].deadline) == TRUE))
			||
			(j > old_ind && atoi(rec[j].taxe) == old_max)

			)
		{
			curr_max = atoi(rec[j].taxe);
			curr_ind = j;
		}
		++j;
	}
	//������ � curr_ind ��������� ������������ �������������, ������ � ������� � ���������� ������� �������
	if (month_compare(month_of_deadline, rec[curr_ind].deadline) == TRUE)
	{
		find_rec = TRUE;
	}
	if (find_rec == TRUE)
	{
		swap_firms(&rec[curr_ind], &rec[curr_minimas++]);
		find_rec = FALSE;

	}

	++i;
	old_max = curr_max;
	old_ind = curr_ind;
	curr_max = atoi(rec[i].taxe);

	curr_ind = i;
	//���� �������� ���� ����� ��������� ����� ������������ ��������
	/*if (find_rec == TRUE)
	{
	show_firm(&rec[old_ind]);
	find_rec = FALSE;
	}
}*/