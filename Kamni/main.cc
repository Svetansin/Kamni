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
				std::cerr << "Произошла ошибка ввода-вывода..." << std::endl;
				exit(1);
			}
			std::cout << "Ввод некорректен. От Вас ожидается число." << std::endl;
			goto re;
		}
		else if (not inps.eof()){
			std::cout << "Простите, но это что за непонятный мусор в конце ввода? Исправьте, пожалуйста." << std::endl;
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
		std::cout << "Число должно быть в интервале от " << min << " до " << max << std::endl;
	}
}


int main(){

	using clk = std::chrono::system_clock;
	std::random_device rd;
	std::minstd_rand rnd{unsigned(clk::now().time_since_epoch().count())};
	std::uniform_int_distribution <> R {15,25};
	std::uniform_int_distribution <> R_comp {1,3};
	int difficulty; //сложность

	do {
		unsigned stones = R(rnd); //генерируем кучку

		difficulty = Range("Выберите желаемый уровень сложности:\n"
										"1.Легкий\n"
										"2.Средний\n"
										"3.Сложный\n"
										"4.Я устал, я ухожу...\n", 1, 4);
		if (difficulty == 4){
			return 0;
		} else
			std::cout << "В кучке " << stones << " камушков." << std::endl;

		while(difficulty != 4){
			std::cout << "За один ход можно взять из кучки 1, 2 или 3 камушка." << std::endl;
			std::cout << std::endl;
			std::cout << "Сколько камушков возьмёте?" << std::endl;
			int S = Range("", 1, std::min (3U, stones));
			stones = stones - S; /* уменьшаем кучку, при том:  	1) если осталось 0 камушков, то игрок проиграл, иначе - ход компа;
																2) если остался 1 камушек, то проиграл комп */
			if (stones < 26){
				std::cout << "В кучке " << stones << " камушков." << std::endl;}

			if (stones == 0 || stones > 25){
				std::cout << "К сожалению, Вы проиграли... Хотите взять реванш?\n" << std::endl;
				break;
			} else {
				unsigned comp;
				//пропишем степень хитрости и беспощадности компа

				if (stones < 5 && difficulty != 1){
					switch(stones){//"Ты не пройдёшь!"
					case 4: comp = 3; break;
					case 3: comp = 2; break;
					case 2: comp = 1; break;
					}
				} else {
					if(difficulty == 1){
						comp = R_comp(rnd); //в зависимости от великого рандома у игрока может быть шанс на победу
					} else if (difficulty == 2){
						switch(S){//у игрока есть небольшой шанс на победу
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
				std::cout << "Ваш соперник взял " << comp << std::endl;
				if (stones == 0 || stones > 25){
					std::cout << "Ураааа, Вы одержали победу над искусственным интеллектом! Хотите сыграть ещё?\n" << std::endl;
					break;
				}
				std::cout << "В кучке " << stones << " камушков." << std::endl;
			}
		}

	} while(true);

	return 0;
}




