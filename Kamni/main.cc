git config --global i18n.commitencodig windows-1252
git config --global i18n.logoutputencoding windows-1252
set LESSCHARSET=latin1

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
				std::cerr << "Ïðîèçîøëà îøèáêà ââîäà-âûâîäà..." << std::endl;
				exit(1);
			}
			std::cout << "Ââîä íåêîððåêòåí. Îò Âàñ îæèäàåòñÿ ÷èñëî." << std::endl;
			goto re;
		}
		else if (not inps.eof()){
			std::cout << "Ïðîñòèòå, íî ýòî ÷òî çà íåïîíÿòíûé ìóñîð â êîíöå ââîäà? Èñïðàâüòå, ïîæàëóéñòà." << std::endl;
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
		std::cout << "×èñëî äîëæíî áûòü â èíòåðâàëå îò " << min << " äî " << max << std::endl;
	}
}


int main(){

	using clk = std::chrono::system_clock;
	std::random_device rd;
	std::minstd_rand rnd{unsigned(clk::now().time_since_epoch().count())};
	std::uniform_int_distribution <> R {15,25};
	std::uniform_int_distribution <> R_comp {1,3};
	int difficulty; //ñëîæíîñòü

	do {
		unsigned stones = R(rnd); //ãåíåðèðóåì êó÷êó

		difficulty = Range("Âûáåðèòå æåëàåìûé óðîâåíü ñëîæíîñòè:\n"
										"1.Ëåãêèé\n"
										"2.Ñðåäíèé\n"
										"3.Ñëîæíûé\n"
										"4.ß óñòàë, ÿ óõîæó...\n", 1, 4);
		if (difficulty == 4){
			return 0;
		} else
			std::cout << "Â êó÷êå " << stones << " êàìóøêîâ." << std::endl;

		while(difficulty != 4){
			std::cout << "Çà îäèí õîä ìîæíî âçÿòü èç êó÷êè 1, 2 èëè 3 êàìóøêà." << std::endl;
			std::cout << std::endl;
			std::cout << "Ñêîëüêî êàìóøêîâ âîçüì¸òå?" << std::endl;
			int S = Range("", 1, std::min (3U, stones));
			stones = stones - S; /* óìåíüøàåì êó÷êó, ïðè òîì:  	1) åñëè îñòàëîñü 0 êàìóøêîâ, òî èãðîê ïðîèãðàë, èíà÷å - õîä êîìïà;
																2) åñëè îñòàëñÿ 1 êàìóøåê, òî ïðîèãðàë êîìï */
			if (stones < 26){
				std::cout << "Â êó÷êå " << stones << " êàìóøêîâ." << std::endl;}

			if (stones == 0 || stones > 25){
				std::cout << "Ê ñîæàëåíèþ, Âû ïðîèãðàëè... Õîòèòå âçÿòü ðåâàíø?\n" << std::endl;
				break;
			} else {
				unsigned comp;
				//ïðîïèøåì ñòåïåíü õèòðîñòè è áåñïîùàäíîñòè êîìïà

				if (stones < 5 && difficulty != 1){
					switch(stones){//"Òû íå ïðîéä¸øü!"
					case 4: comp = 3; break;
					case 3: comp = 2; break;
					case 2: comp = 1; break;
					}
				} else {
					if(difficulty == 1){
						comp = R_comp(rnd); //â çàâèñèìîñòè îò âåëèêîãî ðàíäîìà ó èãðîêà ìîæåò áûòü øàíñ íà ïîáåäó
					} else if (difficulty == 2){
						switch(S){//ó èãðîêà åñòü íåáîëüøîé øàíñ íà ïîáåäó
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
				std::cout << "Âàø ñîïåðíèê âçÿë " << comp << std::endl;
				if (stones == 0 || stones > 25){
					std::cout << "Óðàààà, Âû îäåðæàëè ïîáåäó íàä èñêóññòâåííûì èíòåëëåêòîì! Õîòèòå ñûãðàòü åù¸?\n" << std::endl;
					break;
				}
				std::cout << "Â êó÷êå " << stones << " êàìóøêîâ." << std::endl;
			}
		}

	} while(true);

	return 0;
} 




