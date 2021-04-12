#include <random>
#include <iostream>
#include <chrono>
#include <sstream>

int Check(const char * question)
{
	int result;
	std::string inp;
	re: std::cout << question;
	std::getline (std::cin, inp);
	{
		std::stringstream inps {inp};
		inps >> result;
		if (inps.fail()){
			if (std::cin.fail()){
				std::cerr << "��������� ������ �����-������..." << std::endl;
				exit(1);
			}
			std::cout << "���� �����������. �� ��� ��������� �����." << std::endl;
			goto re;
		}
		else if (not inps.eof()){
			std::cout << "��������, �� ��� ��� �� ���������� ����� � ����� �����? ���������, ����������." << std::endl;
			goto re;
		}

	}
	return result;
}

int Range(const char * question, int min, int max)
{
	int result;
	for(;;) {
		result = Check(question);
		if (result >= min and result <= max)
			return result;
		std::cout << "����� ������ ���� � ��������� �� " << min << " �� " << max << std::endl;
	}
}


int main(){

	using clk = std::chrono::system_clock;
	std::random_device rd;
	std::minstd_rand rnd{unsigned(clk::now().time_since_epoch().count())};
	std::uniform_int_distribution <> R {15,25};
	std::uniform_int_distribution <> R_comp {1,3};
	int difficulty; //���������

	do {
		unsigned stones = R(rnd); //���������� �����

		difficulty = Range("�������� �������� ������� ���������:\n"
										"1.������\n"
										"2.�������\n"
										"3.�������\n"
										"4.� �����, � �����...\n", 1, 4);
		if (difficulty == 4){
			return 0;
		} else
			std::cout << "� ����� " << stones << " ��������." << std::endl;

		while(difficulty != 4){
			std::cout << "�� ���� ��� ����� ����� �� ����� 1, 2 ��� 3 �������." << std::endl;
			std::cout << std::endl;
			std::cout << "������� �������� �������?" << std::endl;
			int S = Range("", 1, std::min (3U, stones));
			stones = stones - S; /* ��������� �����, ��� ���:  	1) ���� �������� 0 ��������, �� ����� ��������, ����� - ��� �����;
																2) ���� ������� 1 �������, �� �������� ���� */
			if (stones < 26){
				std::cout << "� ����� " << stones << " ��������." << std::endl;}

			if (stones == 0 || stones > 25){
				std::cout << "� ���������, �� ���������... ������ ����� ������?\n" << std::endl;
				break;
			} else {
				unsigned comp;
				//�������� ������� �������� � ������������� �����

				if (stones < 5 && difficulty != 1){
					switch(stones){//"�� �� �������!"
					case 4: comp = 3; break;
					case 3: comp = 2; break;
					case 2: comp = 1; break;
					}
				} else {
					if(difficulty == 1){
						comp = R_comp(rnd); //� ����������� �� �������� ������� � ������ ����� ���� ���� �� ������
					} else if (difficulty == 2){
						switch(S){//� ������ ���� ��������� ���� �� ������
						case 1: comp = 3; break;
						case 2: comp = 2; break;
						case 3: comp = 1; break;
						}
					} else {
						for(unsigned i = 25; i > 0; i -= 4){
							if (i == stones){
								comp = R_comp(rnd);
								break;
							}
							if (stones > i){
								comp = stones - i;
								break;
							}
						}
					}
				}
				stones = stones - comp;
				std::cout << "��� �������� ���� " << comp << std::endl;
				if (stones == 0 || stones > 25){
					std::cout << "������, �� �������� ������ ��� ������������� �����������! ������ ������� ���?\n" << std::endl;
					break;
				}
				std::cout << "� ����� " << stones << " ��������." << std::endl;
			}
		}

	} while(true);

	return 0;
}




