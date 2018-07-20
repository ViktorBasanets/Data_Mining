#include "declaration.h"
#include <iostream>

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
#pragma comment(lib, "libiconv.lib")

void timeDelay(size_t sec)
{
	clock_t delay = sec * CLOCKS_PER_SEC;
	clock_t start = clock();
	while (clock() - start < delay);
}
size_t sum_first_link(size_t sum, size_t lim)
{
	if (sum % lim != 0)
		return sum / lim + 1;
	else
		return sum / lim;
}
std::set<std::string> pull_unit(const std::string & txt, const std::string & re, const std::string & ingoing, const std::string & re2, const std::string & ingoing2)
{
	std::string str = boost::regex_replace(txt, boost::regex(re.c_str()), ingoing, boost::regex_constants::format_no_copy);
	std::string temp;
	std::istringstream iss(str);
	std::set<std::string> setlist;
	while (getline(iss, temp))
		if (
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "sports" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "sport" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "sportstable" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "video" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "infographic" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "infographics" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "infographica" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "digest" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "editorial" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "opinion" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "opinions" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "vote" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "history" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "country_russia" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "culture" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "interview" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "photonews" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "tech" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "roundtable" &&
			boost::regex_replace(temp, boost::regex(re2.c_str()), ingoing2, boost::regex_constants::format_no_copy) != "caricature"
			)
			setlist.insert(temp);
	return setlist;
}
std::string convert_month(size_t month)
{
	switch (month)
	{
	case 1:
		return "Jan";
	case 2:
		return "Feb";
	case 3:
		return "Mar";
	case 4:
		return "Apr";
	case 5:
		return "May";
	case 6:
		return "Jun";
	case 7:
		return "Jul";
	case 8:
		return "Aug";
	case 9:
		return "Sep";
	case 10:
		return "Oct";
	case 11:
		return "Nov";
	case 12:
		return "Dec";
	default:
		throw std::exception("Invalid month!!!");
	}
}
int days_in_month(size_t month)
{
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		return 29;
	default:
		throw std::exception("Invalid month!!!");
	}
}
std::string numbers_to_date(size_t x, size_t y, size_t z, const std::string & separator)
{
	std::ostringstream oss;
	if (x < 10) oss << "0" << x << separator;
	else oss << x << separator;

	if (y < 10) oss << "0" << y << separator;
	else oss << y << separator;

	if (z < 10) oss << "0" << z;
	else oss << z;

	return oss.str();
}
std::string convert_encoding(const std::string& data, const std::string& from, const std::string& to)
{
	if (data.empty())
	{
		return std::string();
	}
	iconv_t convert_hnd = iconv_open(to.c_str(), from.c_str());
	if (convert_hnd == (iconv_t)(-1))
	{
		throw std::logic_error("unable to create convertion descriptor");
	}

	const char* in_ptr = const_cast<char*>(data.c_str());
	std::size_t in_size = data.size();
	std::vector<char> outbuf(6 * data.size());
	char* out_ptr = &outbuf[0];
	std::size_t reverse_size = outbuf.size();

	std::size_t result = iconv(convert_hnd, &in_ptr, &in_size, &out_ptr, &reverse_size);

	iconv_close(convert_hnd);
	if (result == (std::size_t)(-1))
	{
		throw std::logic_error("unable to convert");
	}

	return std::string(outbuf.data(), outbuf.size() - reverse_size);
}
/*std::set<std::string> name_for_matching(const std::string & body, const std::string & filename) // function for 
{

	std::ifstream fin(filename.c_str());
	if (!fin.is_open())
	{
		std::cerr << "Can't open file" << filename << std::endl;
		exit(0);
	}
	std::string str;
	std::set<std::string> setstr;
	while (getline(fin, str))
		if (str.size() != 0)
			setstr.insert(str);
	return setstr;
}*/
void name_for_matching(std::set<std::string> & ua, std::set<std::string> & ather) // function for 
{
	setlocale(LC_ALL, "Russian");
	ua = {
		"Р. Абрамович", "А. Абромавичус", "В. Аброськин", "А. Аваков", "Н. Азаров", "С. Аксенов", "А. Александров", "С. Андреев", "Д. Андриевский", "Д. Антонюк", "С. Арбузов",
		"Ю. Артемко", "В. Арьев", "Г. Афанасьев", "Р. Ахметов", "А. Бабицкий", "В. Балога", "А. Баньчук", "Б. Безпалько", "Б. Береза", "О. Березнюк", "Т. Березовец", "Р. Бессмертный",
		"Р. Богатырева", "М. Богданов", "Е. Божок", "Ю. Бойко", "В. Бондаренко", "А. Бородай", "Р. Бортник", "И. Бубенчик", "В. Будько", "О. Бузина", "С. Буць", "Г. Василенко",
		"В. Ващиковский", "А. Вилкул", "Ю. Витренко", "О. Вишняков", "Д. Вовк", "В. Войцицкая", "Ю. Гаврилечко", "М. Гаврилюк", "М. Гайдар", "С. Гайдук", "С. Галушко", "Ю. Гарбуз",
		"А. Геращенко", "А. Герман", "В. Гинько", "Е. Гитлянская", "Е. Глищинская", "В. Гонтарева", "А. Гончаренко", "А. Гопко", "А. Горбатко", "К. Григоришин", "Д. Григорова", "Л. Гриневич",
		"В. Грицак", "А. Гриценко", "В. Гройсман", "И. Грынив", "Е. Губарева", "Т. Гузенкова", "И. Гуменюк", "С. Гусовский", "А. Даниленко", "А. Данилюк", "Д. Дашкевич", "В. Дейнего",
		"Х. Деканоидзе", "В. Демчишин", "Ю. Деревянко", "А. Дещица", "В. Диденко", "Ю. Димент", "А. Дихтяренко", "Н. Дорошенко", "А. Дуда", "А. Дудчак", "С. Дьяков", "В. Ельченко", "А. Ефремов",
		"П. Жебривский", "А. Жигулин", "М. Заборовский", "А. Захарченко", "Э. Згуладзе", "С. Згурец", "В. Землянский", "Г. Зубко", "М. Зыгарь", "Ю. Иванченко", "Ю. Иванющенко", "Е. Идрисов",
		"В. Ищук", "О. Калашников", "С. Каплин", "Н. Карпюк", "В. Касько", "В. Катрюк", "А. Квиташвили", "Г. Кернес", "И. Кива", "С. Кивалов", "В. Кириленко", "А. Клименко", "П. Климкин",
		"И. Климпуш", "Ф. Клинцевич", "В. Кличко", "А. Клюев", "А. Коболев", "О. Кобцева", "М. Коваль", "В. Ковальчук", "Б. Колесников", "Ю. Колобов", "И. Коломойский", "А. Кольченко", "М. Конелиус",
		"А. Коновалов", "И. Кононенко", "Г. Корбан", "В. Коряк", "Р. Коцаба", "А. Кошель", "Р. Кошулинский", "Л. Кравчук", "А. Крищенко", "С. Кубив", "А. Кужель", "Р. Кузьмин", "С. Курченко",
		"В. Куценко", "Л. Кучма", "С. Левочкин", "С. Лещенко", "В. Литвин", "А. Литвиненко", "С. Литинский", "Г. Логвинский", "А. Лозовой", "С. Лойко", "А. Лупейко", "Ю. Луценко", "А. Лысенко",
		"О. Ляшко", "Т. Мазур", "Н. Маломуж", "А. Манчук", "Н. Мартыненко", "Д. Марунич", "Ю. Марушевская", "В. Матвиенко", "А. Матиос", "С. Матусяк", "А. Мацеревич", "А. Мегера", "В. Медведчук",
		"А. Медведько", "С. Мельничук", "А. Мельчуцкий", "С. Меняйло", "М. Микитась", "А. Миллер", "О. Могилевский", "Т. Монтян", "И. Мосийчук", "Г. Москаль", "А. Мотузяник", "В. Муженко", "В. Назаренко",
		"Г. Назаров", "М. Найем", "В. Наливайченко", "А. Новак", "В. Новинский", "П. Овчаренко", "А. Омельченко", "В. Омелян", "Д. Онипко", "А. Онищенко", "В. Орбан", "П. Орловская", "А. Охрименко",
		"А. Павленко", "А. Павличенков", "Е. Палажченко", "П. Паламарчук", "В. Парасюк", "А. Парубий", "М. Пасенюк", "Д. Песков", "П. Петренко", "А. Пивовар", "А. Пивоварский", "В. Пинчук", "И. Плотницкий",
		"М. Погребинский", "Н. Поклонская", "Д. Полищук", "С. Полторак", "Л. Пономарев", "П. Порошенко", "В. Портников", "А. Портнов", "В. Потупчик", "С. Редька", "В. Резниченко", "П. Розенко", "И. Романенко",
		"А. Рыбчук", "С. Рябков", "М. Саакашвили", "Н. Савченко", "А. Садовой", "М. Сайдик", "Н. Селиверстова", "С. Семенченко", "О. Сенцов", "П. Симоненко", "Ю. Сиротюк", "Я. Скиба", "Н. Скорик",
		"О. Слободян", "И. Смилянский", "Е. Соболев", "Б. Соботка", "И. Совсун", "Ю. Солошенко", "Н. Статкевич", "В. Степаненко", "Ю. Стец", "А. Стецко", "В. Стоякин", "Д. Суслов", "Р. Сухан",
		"О. Сыроид", "А. Тарасенко", "С. Тарута", "А. Тетерук", "Ю. Тимошенко", "А. Ткачев", "А. Ткаченко", "К. Томащук", "Г. Трофимчук", "А. Турчинов", "О. Тягнибок", "А. Улюкаев", "И. Фарион",
		"Е. Федченко", "В. Филипчук", "Д. Фирташ", "В. Халецкий", "В. Хотиненко", "В. Христенко", "Р. Худяков", "А. Хунко", "С. Цеголко", "М. Цуркан", "В. Цыбенко", "В. Чалый", "С. Чеботарь",
		"А. Чернушенко", "В. Черныш", "А. Черняк", "Т. Чорновол", "Д. Чудовский", "А. Шевченко", "А. Шевчишин", "В. Шендерович", "З. Шкиряк", "С. Шустер", "Р. Шухевич", "В. Ющенко", "А. Яковенко",
		"М. Яковлева", "А. Янголенко", "В. Янукович", "В. Ярема", "Н. Яресько", "И. Яровая", "А. Ярославский", "Д. Ярош", "А. Яценюк"
	};
	ather = {
		"В. Абакумов", "Ф. Абдалла", "Р. Абрамович", "С. Абэ", "А. Александров", "П. Алли", "Г. Алтухов", "М. Аншаков", "Э. Апакан", "А. Аргат", "А. Арешев", "Л. Арон", "В. Арьев", "Б. Асад", "А. Аслунд",
		"Н. Атаманюк", "П. Ауштрявичюс", "Г. Афанасьев", "Д. Байден", "С. Балмасов", "Р. Балфа", "Р. Бальбек", "Е. Бариев", "О. Барна", "М. Барталмай", "А. Бастрыкин", "Э. Басурин", "С. Батрин",
		"Д. Батчелор", "А. Бекерат", "К. Бендукидзе", "Г. Бердымухамедов", "М. Бернштам", "Л. Бершидский", "П. Беседин", "Я. Бжезинский", "К. Билл", "К. Бильдт", "Ю. Бирюков", "И. Блащук",
		"А. Блинов", "Т. Блэр", "Ш. Бойтельсбахер", "Г. Бокерия", "С. Бородулина", "В. Брандта", "А. Брассер", "Н. Братца", "Ф. Бридлав", "А. Брод", "В. Бучельников", "Д. Буш", "А. Ваджра",
		"Л. Валенса", "В. Виммер", "М. Вихман", "О. Вишняков", "Э. Вуд", "З. Габриэле", "М. Гафни", "А. Гаффаль", "Н. Гварамия", "А. Гедберг", "К. Гернер", "А. Гживинський", "В. Гжимала",
		"Э. Гимулла", "В. Гольц", "М. Горбачев", "П. Грегори", "М. Грегуара", "А. Григас", "Б. Грызлов", "Х. Гуннериуссон", "Г. Гуторов", "Д. Данфорд", "Н. Дедок", "К. Дейкофф", "В. Дейнего",
		"М. Демпси", "Ж. Депардье", "К. Джакомопулос", "Д. Джексон", "М. Джемилев", "Ф. Дзержинский", "Ю. Димент", "С. Дион", "К. Долгов", "А. Долидзе", "Т. Дончев", "Я. Доубрав", "Ж. Дриан",
		"М. Дрокова", "А. Дугин", "Р. Дузэт", "А. Дынер", "Ч. Дэвид", "А. Дюбьен", "Ю. Дюдин", "В. Ельченко", "И. Еремеев", "Е. Ерофеев", "А. Жайнаков", "В. Жарков", "Я. Жарын", "П. Жебривский",
		"М. Жейнова", "Б. Желиба", "А. Жигулин", "В. Жириновский", "Д. Жунусова", "А. Залдостанов", "Г. Зигмар", "М. Золкина", "Д. Ибаррури", "Б. Иванишвили", "В. Иванов", "В. Игрунов", "Е. Идрисов",
		"М. Йегер", "К. Йенсен", "Т. Ильвес", "М. Йованович", "Р. Йозвяк", "Е. Иоппе", "К. Йоханс", "Л. Исламов", "Т. Йустра", "Р. Кадыров", "И. Калакаускас", "М. Калинин", "С. Калниете", "В. Калугин",
		"М. Кантор", "С. Каплин", "В. Карасев", "Ф. Карбер", "М. Карпентер", "К. Карский", "Э. Картер", "Г. Каспаров", "М. Касьянов", "Ю. Катайнен", "В. Катасонов", "С. Като", "Я. Качиньский",
		"О. Кашин", "А. Квасневский", "Г. Квирикашвили", "С. Квит", "Г. Кенен", "Г. Кернес", "Д. Керри", "Д. Клеппер", "Х. Клинтон", "Ф. Клинцевич", "С. Клих", "И. Кобзон", "А. Коболев",
		"О. Кобцева", "В. Кожемяко", "С. Козлов", "Н. Козырев", "Ю. Колобов", "С. Комков", "В. Константинов", "Э. Кордес", "С. Костинский", "С. Коэн", "М. Крамер", "О. Крейчи", "Т. Круз", "О. Крюков",
		"С. Кундиус", "Ю. Куркчи", "Д. Кэмерон", "С. Лавров", "К. Лагард", "С. Ларов", "В. Левковский", "Б. Ложкин", "А. Ломановский", "Г. Лордкипанидзе", "А. Лукашенко", "Т. Лундстедт", "Л. Лурье",
		"Д. Лью", "А. Любимов", "Т. Майкл", "Ш. Майстер", "Д. Макгрегор", "Д. Маккейн", "Н. Маломуж", "М. Мамон", "И. Мандро", "Г. Маргвелашвили", "Я. Марги", "Т. Мариани", "В. Маркин", "М. Марран",
		"Р. Масюлис", "Д. Медведев", "А. Меркель", "С. Милошевич", "Д. Миятович", "Ф. Могерини", "П. Мордаунт", "А. Мордашов", "П. Морель", "П. Морозов", "Е. Москвин", "Н. Муйжниекс", "Г. Мун",
		"В. Муравицкий", "Г. Мустанг", "А. Мустафаев", "К. Мчедлишвили", "Д. Мэтлок", "К. Мюккянен", "Р. Мюцених", "Н. Назарбаев", "С. Нарышкин", "И. Насалик", "Р. Насиров", "Б. Нетаньяху", "А. Нечаев",
		"С. Ниинист", "В. Никитин", "Т. Нишнианидзе", "В. Нулланд", "Б. Обама", "В. Олейник", "Ф. Олланд", "В. Орбан", "П. Орловская", "А. Павловский", "А. Паддингтон", "Д. Пайетт", "С. Пайфер",
		"И. Папанин", "Ф. Пармантье", "Д. Пегов", "У. Перри", "Ф. Пертес", "Д. Песков", "Д. Петреус", "Н. Петров", "Ю. Пилсудский", "М. Пискорский", "А. Погорелый", "Б. Позен", "Н. Поклонская",
		"Д. Порцген", "Э. Преатони", "П. Притцкер", "С. Приходько", "А. Пуков", "А. Пургин", "В. Путин", "Я. Путконен", "Д. Пушилин", "А. Пушков", "К. Пырвулеску", "С. Пятаков", "В. Рабинович",
		"С. Радонежский", "С. Разов", "И. Райнин", "А. Расмуссен", "М. Ренц", "С. Розенберг", "С. Ролдугин", "М. Роллинз", "Л. Рубинштейн", "М. Рубио", "Ю. Рубцов", "М. Рютте", "Л. Сабадош",
		"С. Садаклиев", "Х. Саджан", "Д. Сакварелидзе", "В. Самодуров", "Б. Сандерс", "Ж. Сапир", "Н. Саркози", "Д. Саттер", "Е. Сацкая", "Н. Севостьянова", "В. Селезнёв", "Н. Селиверстова",
		"О. Сенцов", "Ю. Сергеев", "А. Силуанов", "Ф. Сиси", "Д. Смит", "Э. Сноуден", "М. Соколов", "В. Соловьев", "Ю. Солошенко", "П. Сондерс", "Д. Соррос", "А. Спартак", "Л. Стек", "Й. Столтенберг",
		"С. Стюарт", "Р. Сульжик", "К. Суринова", "Д. Суси", "Д. Суслов", "Р. Сухан", "О. Сыроид", "Б. Сэндерс", "В. Сюмар", "А. Талаго", "Д. Теффта", "Б. Тито", "Д. Тозо", "М. Толбоев", "М. Тонер",
		"Я. Тоом", "Н. Топорнин", "Д. Трамп", "Г. Трофимчук", "Г. Труханов", "Э. Трюдо", "Г. Тук", "Д. Туск", "В. Ужулис", "М. Уклеба", "А. Улюкаев", "У. Умеров", "П. Унгурян", "С. Уоррен",
		"Ю. Ушаков", "Э. Уэллс", "Л. Фабиус", "Ч. Фан", "Э. Фаркас", "М. Фейриг", "П. Фельгенгауэр", "Б. Филатов", "В. Филип", "Ф. Фицо", "Б. Фишер", "М. Флауэрной", "Д. Флорин", "А. Фог",
		"Д. Фридман", "И. Фриз", "Ф. Фукуяма", "Й. Хан", "С. Хансен", "C. Херш", "Б. Ходжес", "Н. Хомски", "Ф. Хофманн", "А. Хуг", "Р. Худяков", "А. Хунко", "С. Хусейн", "Г. Цахман", "Т. Цулукиани",
		"М. Цуркан", "М. Чавушоглу", "Н. Челебиджан", "С. Чемезов", "В. Чепурной", "В. Черныш", "А. Черняк", "А. Чеснаков", "Р. Чубаров", "В. Чуркин", "В. Шабунин", "Ю. Швачач", "М. Шефчович",
		"И. Шиминович", "П. Шипилин", "Ж. Ширак", "А. Шитов", "И. Шишкин", "Л. Шлосберг", "Д. Шляпентох", "Я. Шнайдер", "С. Шойгу", "Г. Шойрер", "В. Шокин", "Д. Шолле", "Ф. Штайнмайер", "Д. Шубель",
		"И. Шуневич", "И. Эйдман", "Г. Эйзенкот", "М. Эйро", "Э. Эльдаров", "Р. Эрдоган", "Д. Эрнст", "Ж. Юнкер", "М. Юрьев", "А. Юхансен", "Р. Янсонс", "И. Яровая", "Ч. Яустра"
	};
}
void get_name(dataFromSite & df, const std::set<std::string> & nameUa, const std::set<std::string> & nameAth)
{
	setlocale(LC_ALL, "Russian");
	df.pull_name = pull_unit(df.body, R"#(([А-Я][а-я]+\s)?([А-Я][а-я]+)\s([А-Я][а-я]+))#", "$1 $2 $3\n");
	/*
	//---------- for testing ----------
	std::ofstream out11("d:/out_pull_unit.txt", std::ofstream::out | std::ofstream::app);
	for (auto it = df.pull_name.begin(); it != df.pull_name.end(); ++it) {
		out11 << *it << "\n";
		out11 << "********************************************************************************************************************" << std::endl;
	}
	out11.close();
	out11.clear();
	out11.open("d:/out_body.txt", std::ofstream::out | std::ofstream::app);
	out11 << df.body << std::endl;
	//---------- testing end ----------*
	*/
	//std::ofstream out("d:/namesUa.txt", std::ofstream::out | std::ofstream::app);
	for (auto it = nameUa.begin(); it != nameUa.end(); ++it) {
		//out << *it << "; ";
		for (auto pt = df.pull_name.begin(); pt != df.pull_name.end(); ++pt) {
			
			if (boost::regex_replace(*it, boost::regex(R"#((\w+\.?)\s(\w+))#"), "$2", boost::regex_constants::format_no_copy) ==
				boost::regex_replace(*pt, boost::regex(R"#(([А-Я][а-я]+\s)?([А-Я][а-я]+)\s([А-Я][а-я]+))#"), "$3", boost::regex_constants::format_no_copy)) {
				df.nameUA.insert(boost::regex_replace(*it, boost::regex(R"#((\w+\.?)\s(\w+))#"), "$2 $1", boost::regex_constants::format_no_copy));
				//out << boost::regex_replace(*it, boost::regex(R"#((\w+\.?)\s(\w+))#"), "$2 $1", boost::regex_constants::format_no_copy) << " || ";
			}
			
			//out << boost::regex_replace(*it, boost::regex(R"#((\w+\.?)\s(\w+))#"), "$2", boost::regex_constants::format_no_copy) << " ?= "
			//	<< boost::regex_replace(*pt, boost::regex(R"#((\w+\s)?(\w+)\s(\w+))#"), "$3", boost::regex_constants::format_no_copy) << "\t";
		}
	}
	//out << std::endl;
	//out.close();
	//out.clear();
	//out.open("d:/namesAther.txt", std::ofstream::out | std::ofstream::app);
	for (auto it = nameAth.begin(); it != nameAth.end(); ++it) {
		//out << *it << "; ";
		for (auto pt = df.pull_name.begin(); pt != df.pull_name.end(); ++pt) {
			
			if (boost::regex_replace(*it, boost::regex(R"#((\w+\.?)\s(\w+))#"), "$2", boost::regex_constants::format_no_copy) ==
				boost::regex_replace(*pt, boost::regex(R"#(([А-Я][а-я]+\s)?([А-Я][а-я]+)\s([А-Я][а-я]+))#"), "$3", boost::regex_constants::format_no_copy)) {
				df.nameAther.insert(boost::regex_replace(*it, boost::regex(R"#((\w+\.?)\s(\w+))#"), "$2 $1", boost::regex_constants::format_no_copy));
				//out << boost::regex_replace(*it, boost::regex(R"#((\w+\.?)\s(\w+))#"), "$2 $1", boost::regex_constants::format_no_copy) << " || ";
			}
			
			//out << (boost::regex_replace(*it, boost::regex(R"#((\w+\.?)\s(\w+))#"), "$2", boost::regex_constants::format_no_copy) ==
			//	boost::regex_replace(*pt, boost::regex(R"#(([А-Я][а-я]+\s)?([А-Я][а-я]+)\s([А-Я][а-я]+))#"), "$3", boost::regex_constants::format_no_copy)) << "\t";
		}
	}
	//out << std::endl;
	/*/---------- for testing ----------
	std::ofstream out("d:/namesUa.txt", std::ofstream::out | std::ofstream::app);
	for (auto it = df.nameUA.begin(); it != df.nameUA.end(); ++it) {
		out << *it << "; ";
		out << std::endl;
	}
	out.close();
	out.clear();
	out.open("d:/namesAther.txt", std::ofstream::out | std::ofstream::app);
	for (auto it = df.nameAther.begin(); it != df.nameAther.end(); ++it) {
		out << *it << "; ";
		out << std::endl;
	}
	//---------- testing end ----------*/
	
}
void categ_and_tonality(dataFromSite & df)
{
	srand((size_t)time(nullptr));
	std::vector<std::string> categ{
		"Авиакатастрофа боинга", "Агрессия России", "Агрессия России", "Агрессия России", "Агрессия России", "Агрессия России", "Агрессия России",
		"Агрессия России", "Агрессия России", "Агрессия России", "Беженцы с востока Украины", "Беззакония и репрессии в Украине",
		"Бесчестие украинских политиков", "Бесчестие украинских политиков", "Бесчестие украинских политиков", "Бесчестие украинских политиков",
		"Бесчестие украинских политиков", "Борьба с коррупцией в Украине", "Внешняя политика Украины", "Внешняя политика Украины", "Военнопленные",
		"Военные преступления", "Война на Востоке Украины", "Война на Востоке Украины", "Война на Востоке Украины", "Война на Востоке Украины",
		"Война на Востоке Украины", "Война на Востоке Украины", "Вопросы здравоохранение", "Вопросы Крыма", "Вопросы Крыма", "Вопросы Крыма",
		"Вопросы Крыма", "Вопросы Крыма", "Вопросы Крыма", "Вопросы Крыма", "Вопросы Крыма", "Вопросы Крыма", "Вопросы Крыма", "Вопросы Крыма",
		"ВПК Украины", "Выполнение Минских договоренностей", "Выполнение Минских договоренностей", "Гибридная война", "Гонка вооружений",
		"Гонка вооружений", "Государственный переворот и гражданская война", "Договор об ассоциации ЕC и Украины", "Договор об ассоциации ЕC и Украины",
		"Договор об ассоциации ЕC и Украины", "Жертвы на Востоке Украины", "Иностранные наемники в Украине", "Иностранные наемники в Украине",
		"Иностранные наемники в Украине", "Интересы олигархов", "Интересы олигархов", "Интересы олигархов", "Интересы олигархов", "Коррупция в Украине",
		"Коррупция в Украине", "Коррупция в Украине", "Культурно-политические вопросы", "Международные отношения", "Международные отношения",
		"Миграция из Украины", "Мирное урегулирование конфликта на Востока Украины", "Мирное урегулирование конфликта на Востока Украины",
		"Мирное урегулирование конфликта на Востока Украины", "Мирное урегулирование конфликта на Востока Украины",
		"Мирное урегулирование конфликта на Востока Украины", "Мирные переговоры", "Мирные переговоры", "Мирные переговоры", "Мирные переговоры",
		"Мировой порядок", "Мировой порядок", "Мировой порядок", "Мировой порядок", "Мобилизация в Украине", "Мобилизация в Украине",
		"Нарушение мирных договоренностей", "Нарушение мирных договоренностей", "Нарушение мирных договоренностей", "Нарушение мирных договоренностей",
		"Нарушение мирных договоренностей", "Нарушение мирных договоренностей", "Национализация в Украине", "Национализация в Украине",
		"Национализация в Украине", "Национализация в Украине", "Националистические организации в Украине", "Недоверие к правительсву Украины",
		"Недоверие к правительсву Украины", "Новая холодная война", "Ополчение ЛНР и ДНР", "Ополчение ЛНР и ДНР", "Ополчение ЛНР и ДНР", "Ополчение ЛНР и ДНР",
		"Ополчение ЛНР и ДНР", "Повышение тарифов для населения Украины", "Повышение тарифов для населения Украины", "Помощь Украине от Запада",
		"Помощь Украине от Запада", "Помощь Украине от Запада", "Правоохранительные органы Украины", "Правоохранительные органы Украины",
		"Правоохранительные органы Украины", "Реформирование в Украине", "Российский кризис", "Российский кризис", "Российско-украинские отношения",
		"Российско-украинские отношения", "Российско-украинские отношения", "Российско-украинские отношения", "Россия и Запад", "Россия и Запад",
		"Россия и Запад", "Россия и Запад", "Россия и Запад", "Россия и Запад", "Россия и Запад", "Россия и Запад", "Россия и Запад", "Россия и Запад",
		"Санкции Запада против РФ", "Санкции Запада против РФ", "Санкции Запада против РФ", "Санкции Запада против РФ", "Санкции Запада против РФ",
		"Санкции Запада против РФ", "Стихийные бедствия в Украине", "Террористические акты в Украине", "Торговля людьми в Украине", "Торговля людьми в Украине",
		"Торговля людьми в Украине", "Торговля оружием в Украине", "Торговля оружием в Украине", "Торговля оружием в Украине", "Транспортно-грузовые перевозки",
		"Транспортно-грузовые перевозки", "Украина и Запад", "Украина и Запад", "Украина и Запад", "Украина и Запад", "Украина и Запад", "Украина и Запад",
		"Украина и Запад", "Украина и Запад", "Украина и Запад", "Украина и Запад", "Украинский кризис", "Украинский кризис", "Украинский кризис",
		"Украинский кризис", "Украинский кризис", "Украинский кризис", "Украинский кризис", "Украинский кризис", "Украинский кризис", "Украинский кризис",
		"Украинский кризис", "Украинский кризис", "Украинский кризис", "Цензура в Украине", "Экономические вопросы", "Экономические вопросы",
		"Экономические вопросы", "Экономические вопросы", "Экономические вопросы", "Экономические вопросы", "Экономические вопросы", "Энергетические вопросы",
		"Энергетические вопросы", "Энергетические вопросы", "Энергетические вопросы", "Энергетические вопросы"
	};
	std::vector<std::string> tonaly{
		"Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально",
		"Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально",
		"Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально",
		"Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально", "Нейтрально",
		"Нейтрально/Отрицательно", "Нейтрально/Отрицательно", "Нейтрально/Отрицательно", "Нейтрально/Отрицательно", "Нейтрально/Отрицательно",
		"Нейтрально/Отрицательно", "Нейтрально/Отрицательно", "Нейтрально/Отрицательно", "Нейтрально/Отрицательно", "Нейтрально/Отрицательно",
		"Нейтрально/Отрицательно", "Нейтрально/Отрицательно", "Нейтрально/Отрицательно", "Нейтрально/Отрицательно", "Нейтрально/Отрицательно",
		"Нейтрально/Положительно", "Нейтрально/Положительно", "Нейтрально/Положительно", "Нейтрально/Положительно", "Нейтрально/Положительно",
		"Отрицательно", "Отрицательно",
		"Положительно"
	};

	int cat = rand() % categ.size();
	int ton = rand() % tonaly.size();

	df.category = categ.at(cat);
	df.tonality = tonaly.at(ton);
}
std::string part_body_tofile(const std::string & body, int sum)
{
	if (sum >= int(body.size()))
		return body;

	std::string str(body), result;
	std::string::iterator label;
	int i = 0;
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if (*it == '.')
			label = it;
		if (i++ == sum)
			break;
	}
	if (i > sum)
		for (auto it = str.begin(); it != label + 1; ++it)
			result += *it;
	else result = str;

	return result;
}

// methods class parsingSites
parsingSites::parsingSites()
	: m_month(0) {}
parsingSites::parsingSites(const std::string & host, const std::string & port, size_t month)
	: m_host(host), m_port(port), m_raw(""), m_month(month), m_setlink(std::set<std::string>()) {}
void parsingSites::create(const std::string & host, const std::string & port, size_t month)
{
	m_raw.clear();
	m_port = port;
	m_host = host;
	m_month = month;
	m_setlink = std::set<std::string>();
}
void parsingSites::request_GET(std::ostream & rs, const std::string & lnk)
{
	rs << "GET " << lnk << " HTTP/1.0\r\n";
	rs << "Host: " << m_host << "\r\n";
	rs << "User-Agent: Mozilla/5.0 (Windows NT 6.1; rv:47.0) Gecko/20100101 Firefox/47.0\r\n";
	rs << "Accept: */*\r\n";
	rs << "Connection: close\r\n\r\n";
}
bool parsingSites::answer(std::istream & ir)
{
	std::string http_ver;
	unsigned int status_code;
	std::string status_mess;
	ir >> http_ver;
	ir >> status_code;
	getline(ir, status_mess);

	if (!ir || http_ver.substr(0, 5) != "HTTP/")
	{
		std::cerr << "Invalid response!" << std::endl;
		return false;
	}
	if (status_code != 200)
	{
		std::cerr << "Response returned with staus code " << status_code << std::endl;
		return false;
	}
	return true;
}
std::string parsingSites::save_answer(boost::asio::ip::tcp::socket & sock, boost::asio::streambuf & strbuf, std::istream & ir)
{
	std::string temp, str;
	boost::system::error_code error;
	while (boost::asio::read(sock, strbuf, boost::asio::transfer_at_least(1), error))
		;
	while (std::getline(ir, temp))
		str += temp;
	return str;
}
std::string parsingSites::save_answer(boost::asio::ssl::stream<boost::asio::ip::tcp::socket> & sock, boost::asio::streambuf & strbuf, std::istream & ir)
{
	std::string temp, str;
	boost::system::error_code error;
	while (boost::asio::read(sock, strbuf, boost::asio::transfer_at_least(1), error))
		;
	while (std::getline(ir, temp))
		str += temp;
	return str;
}
bool parsingSites::get_connect(const std::string & link)
{
	setlocale(0, "");
	using boost::asio::ip::tcp;
	using boost::asio::ssl::context;
	using boost::asio::ssl::stream;
	using boost::asio::ssl::rfc2818_verification;

	try {
		boost::asio::io_service ioservice;
		tcp::resolver resolver(ioservice);
		tcp::resolver::query query(m_host, m_port);
		auto endpoint_iterator = resolver.resolve(query);

		boost::asio::streambuf request;
		std::ostream req_stream(&request);
		request_GET(req_stream, link);
		boost::asio::streambuf response;
		std::istream in_res(&response);

		std::string text;

		if (m_port != "https")
		{
			// ---------------- for http ---------------- //
			tcp::socket socket(ioservice);
			boost::asio::connect(socket, endpoint_iterator);
			boost::asio::write(socket, request);
			boost::asio::read_until(socket, response, "\r\n");

			if (answer(in_res))
				m_raw += save_answer(socket, response, in_res);
		}
		else
		{
			// ---------------- for https ---------------- //
			context ctext(context::sslv23);
			ctext.set_default_verify_paths();
			stream<tcp::socket> socket(ioservice, ctext);

			connect(socket.lowest_layer(), endpoint_iterator);

			socket.set_verify_mode(boost::asio::ssl::verify_none);
			socket.set_verify_callback(rfc2818_verification(m_host));
			socket.handshake(stream<tcp::socket>::client);

			write(socket, request);
			read_until(socket, response, "\r\n");

			if (answer(in_res))
				m_raw += save_answer(socket, response, in_res);
		}
	}
	catch (std::exception & ex)
	{
		std::cerr << "Exception from get_connect() function: " << ex.what() << std::endl;
	}

	if (m_raw.size() != 0)
		return true;
	else
	{
		std::cerr << "The m_raw is empty!!!\n";
		return false;
	}
}
void parsingSites::walk_on_links(const std::string & lnk)
{
	get_connect(lnk);
	timeDelay(rand() / 5000);
}
std::string parsingSites::port()
{
	return m_port;
}
std::string parsingSites::host()
{
	return m_host;
}
std::string parsingSites::month(const std::string & label)
{
	setlocale(0, "");
	std::ostringstream oss;
	if (label == "digit")
		if (m_month > 0 && m_month < 10)
			oss << "0" << m_month;
		else oss << m_month;
	else
		switch (m_month)
		{
		case 1: return "января";
		case 2: return "февраля";
		case 3: return "марта";
		case 4: return "апреля";
		case 5: return "мая";
		case 6: return "июня";
		case 7: return "июля";
		case 8: return "августа";
		case 9: return "сентября";
		case 10: return "октября";
		case 11: return "ноября";
		case 12: return "декабря";
		}
	return oss.str();
}
void parsingSites::ina_single_row(std::string & str)
{
	std::string temp, str2;
	std::istringstream iss(str);
	while (iss >> temp)
		str2 += (temp + ' ');
	str = str2;
}
void parsingSites::ina_single_rowconv(std::string & str)
{
	std::string temp, str2;
	std::istringstream iss(str);
	while (iss >> temp)
	{
		try
		{
			temp = convert_encoding(temp, "UTF-8", "CP1251");
		}
		catch (std::exception & ex)
		{
			std::ofstream lout("d:/log.txt", std::ofstream::out | std::ofstream::app);
			lout << "Exception from ina_singele_rowconv(): " << ex.what() << "! " << temp << "!!! ";

			std::string ind;
			for (auto it = temp.begin(); it != temp.end(); ++it)
			{
				std::string ch;
				ch += *it;
				try
				{
					ch = boost::regex_replace(ch, boost::regex(R"#([\!-\}]*)#"), "$0", boost::regex_constants::format_no_copy);
					ind += ch;
				}
				catch (std::exception & ex)
				{
					std::cout << "Exception word: " << ex.what() << std::endl;
				}
			}
			temp = ind;
			lout << temp << std::endl;
		}


		str2 += (temp + " ");
	}
	str = str2;
}
dataFromSite parsingSites::get_data(const std::string & link, const std::string & rdate,
	const std::string & ingoing_date, const std::string & ingoing_month, const std::string & ingoing_year,
	const std::string & rcountry, const std::string & rpublisher, const std::string & rlink, const std::string & rtitle,
	const std::string & rsubtitle, const std::string & rbody)
{
	m_raw.clear();
	walk_on_links(link);
	ina_single_rowconv(m_raw);
	dataFromSite dfs;
	std::string tempstr;
	
	// -------- for testing
	//std::ofstream out("d:/body_rt.txt", std::ofstream::out | std::ofstream::app);
	//out << m_raw << std::endl;
	// -------- end testing

	if ((boost::regex_replace(m_raw, boost::regex(rdate.c_str()), ingoing_month, boost::regex_constants::format_no_copy) == month()
		|| boost::regex_replace(m_raw, boost::regex(rdate.c_str()), ingoing_month, boost::regex_constants::format_no_copy) == month("word"))
		&& boost::regex_replace(m_raw, boost::regex(rdate.c_str()), ingoing_year, boost::regex_constants::format_no_copy) == "2016")
		dfs.pdate = boost::regex_replace(m_raw, boost::regex(rdate.c_str()), ingoing_date, boost::regex_constants::format_no_copy);

	tempstr = boost::regex_replace(m_raw, boost::regex(rcountry.c_str()), "$1", boost::regex_constants::format_no_copy);
	if (tempstr.size() != 0)
		dfs.country = tempstr;
	else if (m_host == "ukraina.ru" || m_host == "russian.rt.com" || m_host == "tass.ru")
		dfs.country = "Россия";

	tempstr = boost::regex_replace(m_raw, boost::regex(rpublisher.c_str()), "$1", boost::regex_constants::format_no_copy);
	if (tempstr.size() != 0)
		dfs.publisher = tempstr;
	else
		dfs.publisher = m_host;

	tempstr = boost::regex_replace(m_raw, boost::regex(rlink.c_str()), "$1", boost::regex_constants::format_no_copy);
	if (tempstr.size() != 0)
		dfs.link = tempstr;
	else
		dfs.link = m_port + "://" + m_host + link;

	tempstr = boost::regex_replace(m_raw, boost::regex(rtitle.c_str()), "$1", boost::regex_constants::format_no_copy);
	if (tempstr.size() != 0)
		dfs.body += (tempstr + ". ");
	tempstr = boost::regex_replace(m_raw, boost::regex(rsubtitle.c_str()), "$1", boost::regex_constants::format_no_copy);
	if (tempstr.size() != 0)
		dfs.body += (tempstr + ". ");
	tempstr = boost::regex_replace(m_raw, boost::regex(rbody.c_str()), "$1", boost::regex_constants::format_no_copy);
	if (tempstr.size() != 0)
		dfs.body += tempstr;
	
	// --------------- for testing ---------------
	//std::ofstream out("d:/body_rt.txt", std::ofstream::out | std::ofstream::app);
	//out << dfs.link << "\t" << m_raw << std::endl;
	// --------------- end testing ---------------

	dfs.body = boost::regex_replace(dfs.body, boost::regex(R"#(<aside .*?>.*?</aside>)#"), " ", boost::regex_constants::format_default);
	dfs.body = boost::regex_replace(dfs.body, boost::regex(R"#(<strong>.*?</strong>)#"), " ", boost::regex_constants::format_default);
	dfs.body = boost::regex_replace(dfs.body, boost::regex(R"#(<.*?>)#"), " ", boost::regex_constants::format_default);
	dfs.body = boost::regex_replace(dfs.body, boost::regex(R"#(\&\w+\;)#"), " ", boost::regex_constants::format_default);
	dfs.body = boost::regex_replace(dfs.body, boost::regex(R"#(\.{2,10})#"), ". ", boost::regex_constants::format_default);
	dfs.body = boost::regex_replace(dfs.body, boost::regex(R"#(\s{2,10})#"), " ", boost::regex_constants::format_default);

	std::set<std::string> name_ua, name_ather;
	name_for_matching(name_ua, name_ather);
	get_name(dfs, name_ua, name_ather);
	categ_and_tonality(dfs);
	/*
	// ------- for testing -------
	std::ofstream out("d:/out_test.txt", std::ofstream::out | std::ofstream::app);
	out << dfs.body << std::endl;
	// ------- testing end -------
	*/
	
	return dfs;
}
void parsingSites::get_dataFomSites(const std::string & quer0, const std::string & quer1, std::string nfile)
{

	if (int(m_month) < 1 || int(m_month) > 12)
	{
		std::cout << "Invalid month!!!\n";
		exit(0);
	}

	size_t all_days = days_in_month(m_month);
	size_t limit = 0;
	size_t SUM = 0;
	size_t SUM_first_link = 0;
	size_t count = 1;
	std::string link;
	srand((size_t)time(nullptr));

	m_raw.clear();
	m_setlink.clear();

	if (m_host == "inosmi.ru")
	{
		limit = 100;
		link = "/services/search/getmore/?search_area=all&date_from=" + numbers_to_date(2017, m_month, 1, "-") + "&date_to=" + numbers_to_date(2017, m_month, all_days, "-") + "&query%5B%5D=" + quer0 + "&limit=" + to_str(limit) + "&offset=";
		if (!get_connect(link + to_str(0)))
			exit(0);
		SUM = pull_number<int>(convert_encoding(boost::regex_replace(m_raw, boost::regex(R"#(<div\sclass=\"search__results\">.*?<span>(.*?)</span>)#"), "$1", boost::regex_constants::format_no_copy), "UTF-8", "CP1251"));
		std::cout << "Find all links: " << SUM << std::endl;
		SUM_first_link = sum_first_link(SUM, limit);

		for (size_t i = 1; i < SUM_first_link; i++)
			walk_on_links(link + to_str(i*limit));
		m_setlink = pull_unit(m_raw, R"#(<h1 class=\".*?\"><a href=\"(.*?)\">.*?</a>)#", "$1\n");
		
		// --------- for test ----------
		//std::ofstream out10("d:/test_out_text.txt");
		// ------- for test end --------
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#(<time class=\"article-footer__date\".*?\">[\w,\s]*(\d+)/(\d+)/(\d+)\s+[\d,\:]*</time>)#", "$1.$2.$3", "$2", "$3",
				R"#(<address class=\"article-magazine article-header-magazine-top\">.*?<a.*?rel=\"publisher\">.*?</a>[\w,\s]*<a href=\"/magazines/\?country=country_[\w,-]+\">(.*?)</a>)#",
				R"#(<address class=\"article-magazine article-header-magazine-top\">.*?<a.*?rel=\"publisher\">(.*?)</a>[\w,\s]*<a href=\"/magazines/\?country=country_[\w,-]+\">.*?</a>)#",
				R"#(<div class=\"article-footer__source\">.*?<a href=\"(.*?)\")#",
				R"#(<h1 class=\"article-header__title\">(.*?)</h1>)#",
				R"#(<p class=\"article-header__announce\">(.*?)</p>)#",
				R"#(<div class=\"article-body\">(.*?)</div>)#");
			//out10 << dfs.body << std::endl;
			
			// --------- for test ----------
			//out10 << "country.size() = " << dfs.country.size() << '\t' << "category.size() = " << dfs.category.size() << '\t' << "body.size() = " << dfs.body.size() << '\t' << "nameAther.size() = " << dfs.nameAther.size() << '\t' << "nameUA = " << dfs.nameUA.size() << '\t' << "publisher.size() = " << dfs.publisher.size() << '\t' << std::endl;
			// ------- for test end --------
			
			if (dfs.body.size() != 0 && dfs.country != "Украина" &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				//save_to_file(nfile, dfs);
				save_report(dfs, nfile);
			}
			system("cls");
			//if (count == 10) break;
		}

		/*// --------- for test ----------
		out10 << "---- nameAther ----\n";
		for (auto it = m_data.begin(); it != m_data.end(); ++it) {
			for (auto pt = it->nameAther.begin(); pt != it->nameAther.end(); ++pt)
				out10 << *pt << "; ";
			out10 << std::endl;
		}
		out10 << "\n---- nameUA ----\n";
		for (auto it = m_data.begin(); it != m_data.end(); ++it) {
			for (auto pt = it->nameUA.begin(); pt != it->nameUA.end(); ++pt)
				out10 << *pt << "; ";
			out10 << std::endl;
		}
		// ------- for test end --------*/
	}
	else if (m_host == "ukraina.ru")
	{
		std::set<std::string> tempset;
		for (size_t i = 1; i <= all_days; i++)
		{
			std::ostringstream oss;
			oss << "/archive/" << numbers_to_date(2017, m_month, i, "") << "/";
			tempset.insert(oss.str());
		}
		//std::ofstream out_test("D:\\out_test.txt");
		//for (auto it = tempset.begin(); it != tempset.end(); ++it)
		//	out_test << *it << std::endl;

		for (auto it = tempset.begin(); it != tempset.end(); ++it)
			walk_on_links(*it);
		m_setlink = pull_unit(m_raw, R"#(<h3\s+class=\".*?\">\s?<a\s+href=\"(.*?)\">)#", "$1\n");
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{

			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#(<time datetime=\"(\d+)\.(\d+)\.(\d+)\">)#", "$1.$2.$3", "$2", "$3",	// pdate
				R"#()#",	// country
				R"#(<div class=\"article_person_rank\"><a.*?>(.*?)</a>)#",	// publisher
				R"#(<p><em>.*?</em><.*?><a href=\"(.*?)\"\s)#",	// link
				R"#(<h1>(.*?)</h1>)#",	// title
				R"#(<p class=\"article_lead\">(.*?)</p>)#",	// subtitle
				R"#(<div class=\"full_text\">(.*?)</div>)#");	// body
			if (dfs.body.size() != 0 && dfs.country != "Украина" &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				//save_to_file(nfile, dfs);
				save_report(dfs, nfile);
			}
			system("cls");
			//if (count == 50) break;
		}

	}
	else if (m_host == "russian.rt.com")
	{
		limit = 10;
		link = "/search?q=" + quer0 + "&type=News&df="
			+ numbers_to_date(1, m_month, 2017, "-") + "&dt="
			+ numbers_to_date(all_days, m_month, 2017, "-") + "&page=";

		if (!get_connect(link + to_str(1)))
			exit(0);
		SUM = pull_number<int>(
			convert_encoding(boost::regex_replace(m_raw,
				boost::regex(R"#(<p class=\"search-serp__total\">(.*?)</p>)#"),
				"$1", boost::regex_constants::format_no_copy),
				"UTF-8", "CP1251")
			);
		SUM_first_link = sum_first_link(SUM, limit);
		for (size_t i = 1; i < SUM_first_link + 1; i++)
			walk_on_links(link + to_str(i));
		//std::ofstream out0("d:/raw_rt.txt", std::ofstream::out | std::ofstream::app);
		//out0 << m_raw << std::endl;
		m_setlink = pull_unit(m_raw, R"#(<a\s*class=\"link\s*link_color\"\s*href=\"(.*?)\">)#", "$1\n");
		std::ofstream out("d:/body_rt.txt", std::ofstream::out | std::ofstream::app);
		//for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		//	out << *it << std::endl;
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#(<div class=\"article__date\s+\"><time class=\"date\s*\">\s*(\d+)\s+(\w+)\s+(\d+)[\,|\d|\:|\s]+</time></div>)#", "$1 $2 $3", "$2", "$3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#(<h1 class=\"article__heading.*?\">(.*?)</h1>)#",	// title
				R"#(<div class=\"article__summary.*?\">(.*?)</div>)#",	// subtitle
				R"#(<div class=\"article__text.*?\">(.*?)</div>)#");	// body

			if (dfs.body.size() != 0 && dfs.country != "Украина" &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0) && dfs.publisher.size() != 0) {
				m_data.push_back(dfs);
				//save_to_file(nfile, dfs);
				save_report(dfs, nfile);
			}
			out << dfs.body << std::endl;
			//if (count > 10) break;
			
			system("cls");

		}
	}
	else if (m_host == "tass.ru")
	{
		std::ifstream fin("D:\\in_files\\first_link_tass.txt");
		std::string temp;
		while (getline(fin, temp))
			m_raw += (temp + '\n');
		fin.close();
		//fin.open("D:\\in_files\\first_link_tass.txt", std::ios_base::trunc);
		if (m_raw.size() == 0)
		{
			std::cout << "File with link, which is located at \"D:\\in_files\\first_link_tass.txt\" is empty!!!";
			exit(0);
		}

		std::set<std::string> tempset = pull_unit(m_raw, R"#(GET\s+(/search.*?)\s+HTTP)#", "$1\n");
		
		m_raw.clear();
		for (auto it = tempset.begin(); it != tempset.end(); ++it)
			walk_on_links(*it);

		tempset = pull_unit(m_raw, R"#(<a\s+class=\\"b-news-item__title.*?href=\\"(.*?)\"\s+target=)#", "$1###\n");
		
		

		for (auto it = tempset.begin(); it != tempset.end(); ++it)
			m_setlink.insert(boost::regex_replace(*it, boost::regex(R"#(\\(.*?)\\(.*?)\\###)#"), "$1$2", boost::regex_constants::format_no_copy));

		//std::ofstream out_test("D:\\out_test.txt");
		//for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		//	out_test << *it;

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#(<span class=\"b-material__date\">(\d+)\s+(\w+)[\,|\d|\:|\s]+</span>)#", "$1 $2 2016", "$2", "",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#(<h1 .*?>(.*?)</h1>)#",	// title
				R"#(<span\s+itemprop=\"description\"\s+class=\"b-material__preview\">(.*?)</span>)#",	// subtitle
				R"#(<div class=\"b-material-text__l js-mediator-article\">(.*?)</div>)#");	// body
			if (dfs.body.size() != 0 && dfs.country != "Украина" &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				//save_to_file(nfile, dfs);
				save_report(dfs, nfile);
			}
			system("cls");
			//if (count == 50) break;
		}

	}
	else if (m_host == "vesti.az")
	{
		link = "/search?keyword=" + quer0 + "&yt0=";
		if (!get_connect(link)) exit(0);
		m_raw = boost::regex_replace(m_raw, boost::regex(R"#(<li>\s*<span>\d+:\d+\s*(\d+\.(\d+)\.\d+).*?</span><a\s+href=\"(.*?)\s*\"\s*title=)#"),
			"$2###$3###\n", boost::regex_constants::format_no_copy);
		std::istringstream iss(m_raw);
		std::string temp;
		while (getline(iss, temp))
			if (boost::regex_replace(temp, boost::regex(R"#((\d+)\#\#\#(.*?)\#\#\#)#"), "$1", boost::regex_constants::format_no_copy) == month())
				m_setlink.insert(boost::regex_replace(temp, boost::regex(R"#((\d+)\#\#\#(.*?)\#\#\#)#"), "$2", boost::regex_constants::format_no_copy));
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "haqqin.az")
	{
		link = "/search/" + quer0;
		if (!get_connect(link))
			exit(0);
		std::set<std::string> tempset = pull_unit(m_raw, R"#(<a\s+class=\"news\s*news_horizontally\"\s+href=\"http://haqqin.az(.*?)\">)#", "$1\n");
		link = "/search/" + quer1;
		if (!get_connect(link))
			exit(0);
		m_setlink = pull_unit(m_raw, R"#(<a\s+class=\"news\s*news_horizontally\"\s+href=\"http://haqqin.az(.*?)\">)#", "$1\n");
		for (auto it = tempset.begin(); it != tempset.end(); ++it)
			m_setlink.insert(*it);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "ru.sputnik.az")
	{
		limit = 100;
		std::string prefix = "/services/search/getmore/?types%5B%5D=article&search_area=body&query%5B%5D=" + quer0 + "&limit="
			+ to_str(limit) + "&offset=";
		std::string sufix = "&sort=date&interval=period&date_from="
			+ numbers_to_date(2016, m_month, 1, "-") + "&date_to="
			+ numbers_to_date(2016, m_month, all_days, "-");
		link = prefix + to_str(0) + sufix;
		if (!get_connect(link)) exit(0);
		SUM = pull_number<int>(convert_encoding(boost::regex_replace(m_raw,
			boost::regex(R"#(<div\s+class=\"search__results\">.*?<span>(.*?)</span>)#"),
			"$1", boost::regex_constants::format_no_copy),
			"UTF-8", "CP1251"));
		SUM_first_link = sum_first_link(SUM, limit);
		for (size_t i = 0; i < SUM_first_link; i++)
			walk_on_links(prefix + to_str(i) + sufix);
		m_setlink = pull_unit(m_raw, R"#(<li\s+class=\"b-plainlist__item\".*?<a\s+href=\"(.*?)\">)#", "$1\n");
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "www.lragir.am")
	{
		link = "/index/rus/0/search/view?q=" + quer0 + "|"
			+ numbers_to_date(2016, m_month, 1, "") + "|"
			+ numbers_to_date(2016, m_month, all_days, "");
		if (!get_connect(link)) exit(0);
		std::set<std::string> tempset = pull_unit(m_raw, R"#(<li\s+class=\"l1\s*thumb\"><a\s+href=\"(.*?)\"\s*)#", "$1\n");

		link = "/index/rus/0/search/view?q=" + quer1 + "|"
			+ numbers_to_date(2016, m_month, 1, "") + "|"
			+ numbers_to_date(2016, m_month, all_days, "");
		if (!get_connect(link)) exit(0);
		m_setlink = pull_unit(m_raw, R"#(<li\s+class=\"l1\s*thumb\"><a\s+href=\"(.*?)\"\s*)#", "$1\n");

		for (auto it = tempset.begin(); it != tempset.end(); ++it)
			m_setlink.insert(*it);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "news.am")
	{
		link = "/rus/search/?q=" + quer0 + "&seintitle=on&withalw=on&daterange="
			+ convert_month(m_month) + "+01%2C+2016+-+" + convert_month(m_month) + "+" + to_str(all_days)
			+ "%2C+2016&days=&projects%5Bnews%5D=on&themes%5B10%5D=on&themes%5B11%5D=on&themes%5B13%5D=on&themes%5B12%5D=on&themes%5B14%5D=on&locations%5B9%5D=on";
		if (!get_connect(link))
			exit(0);
		std::set<std::string> tempset = pull_unit(m_raw, R"#(<div\s+class=\"articles-content\">.*?<div\s+class=\"describe\">\s*<div\s+class=\"title\">\s*<a\s+href=\"(.*?)\"\s+)#", "$1\n");

		link = "/rus/search/?q=" + quer1 + "&seintitle=on&withalw=on&daterange="
			+ convert_month(m_month) + "+01%2C+2016+-+" + convert_month(m_month) + "+" + to_str(all_days)
			+ "%2C+2016&days=&projects%5Bnews%5D=on&themes%5B10%5D=on&themes%5B11%5D=on&themes%5B13%5D=on&themes%5B12%5D=on&themes%5B14%5D=on&locations%5B9%5D=on";
		if (!get_connect(link))
			exit(0);
		m_setlink = pull_unit(m_raw, R"#(<article class=\"article-item\".*?<a href=\"(.*?)\"\s+)#", "/$1\n");
		for (auto it = tempset.begin(); it != tempset.end(); ++it)
			m_setlink.insert(*it);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "www.tert.am")
	{
		link = "/ru/news/search?cat=&from_date=" + numbers_to_date(2016, m_month, 1, "-")
			+ "&to_date=" + numbers_to_date(2016, m_month, all_days, "-") + "&q=" + quer0;
		if (!get_connect(link))
			exit(0);
		std::set<std::string> tempset = pull_unit(m_raw, R"#(<div\s+class=\"news-blocks\"><a href=\"http://www.tert.am(.*?)\">)#", "$1\n");

		link = "/ru/news/search?cat=&from_date=" + numbers_to_date(2016, m_month, 1, "-")
			+ "&to_date=" + numbers_to_date(2016, m_month, all_days, "-") + "&q=" + quer1;
		if (!get_connect(link))
			exit(0);
		m_setlink = pull_unit(m_raw, R"#(<div\s+class=\"news-blocks\"><a href=\"http://www.tert.am(.*?)\">)#", "$1\n");

		for (auto it = tempset.begin(); it != tempset.end(); ++it)
			m_setlink.insert(*it);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "naviny.by")
	{
		link = "/search?key=" + quer0 + "&from[date]="
			+ numbers_to_date(m_month, 1, 2016, "/") + "&to[date]="
			+ numbers_to_date(m_month, all_days, 2016, "/") + "&author=&rubric=All&sort_by=created&page=";
		for (int i = 0; i < 5; i++)
			walk_on_links(link + to_str(i));
		link = "/search?key=" + quer1 + "&from[date]="
			+ numbers_to_date(m_month, 1, 2016, "/") + "&to[date]="
			+ numbers_to_date(m_month, all_days, 2016, "/") + "&author=&rubric=All&sort_by=created&page=";
		for (int i = 0; i < 5; i++)
			walk_on_links(link + to_str(i));
		m_setlink = pull_unit(m_raw, R"#(<div class="media">.*?<h3\s+class=\"media-heading\">\s*<a\s+href=\"http://naviny.by(.*?)\">)#", "$1\n");
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "www.belaruspartisan.org")
	{
		limit = 15;
		std::string prefix = "/ax/search.feeder.php?q=" + quer0 + "&sid=97&pd1=1469998800&pd2=1472590800&st=date&pg=", sufix = "&lang=";
		if (!get_connect(prefix + to_str(0) + sufix)) exit(0);
		SUM = pull_number<int>(boost::regex_replace(m_raw,
			boost::regex(R"#(<b>(.*?)</b>)#"), "$1", boost::regex_constants::format_no_copy));
		SUM_first_link = sum_first_link(SUM, limit);
		for (unsigned int i = 1; i < SUM_first_link; i++)
			walk_on_links(prefix + to_str(i) + sufix);

		std::string temp(m_raw);
		m_raw.clear();
		prefix = "/ax/search.feeder.php?q=" + quer1 + "&sid=97&pd1=1469998800&pd2=1472590800&st=date&pg=";
		if (!get_connect(prefix + to_str(0) + sufix)) exit(0);
		SUM = pull_number<int>(boost::regex_replace(m_raw,
			boost::regex(R"#(<b>(.*?)</b>)#"), "$1", boost::regex_constants::format_no_copy));
		SUM_first_link = sum_first_link(SUM, limit);
		for (unsigned int i = 1; i < SUM_first_link; i++)
			walk_on_links(prefix + to_str(i) + sufix);

		m_raw += temp;
		m_raw = boost::regex_replace(m_raw, boost::regex(R"#(<h3><a\s+.*?href=\"(.*?)\">.*?<span\s+class=\"meta\">[\w,:]+\s+\d+/(\d+)/(\d+)</span>)#"),
			"$3###$2###$1###\n", boost::regex_constants::format_no_copy);
		std::istringstream iss(m_raw);
		boost::regex re(R"#((\d+)\s*\#\#\#\s*(\d+)\s*\#\#\#\s*(.*?)\#\#\#)#");
		while (getline(iss, temp))
			if (boost::regex_replace(temp, re, "$1", boost::regex_constants::format_no_copy) == "2016" &&
				boost::regex_replace(temp, re, "$2", boost::regex_constants::format_no_copy) == month())
				m_setlink.insert(boost::regex_replace(temp, re, "$3", boost::regex_constants::format_no_copy));
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "www.belta.by")
	{
		limit = 15;
		std::string prefix = "/search/getExtendedResults/page/";
		std::string sufix = "/?query=" + quer0 + "&phrase=&any_of_words=&none_of_words=&group=0&from_day="
			+ numbers_to_date(1, m_month, 2016, ".") + "&to_day="
			+ numbers_to_date(all_days, m_month, 2016, ".") + "&sort_by=desc";
		if (!get_connect(prefix + to_str(1) + sufix)) exit(0);
		ina_single_row(m_raw);

		SUM = pull_number<int>(convert_encoding(boost::regex_replace(m_raw,
			boost::regex(R"#(<div class="search_res_info">.*?</form>.*?</b>(.*?)<div class=\"search_h_line\">)#"),
			"$1", boost::regex_constants::format_no_copy),
			"UTF-8", "CP1251"));
		SUM_first_link = sum_first_link(SUM, limit);
		m_raw.clear();

		for (unsigned int i = 1; i < SUM_first_link; i++)
			walk_on_links(prefix + to_str(i) + sufix);

		std::string temp(m_raw);
		m_raw.clear();

		sufix = "/?query=" + quer1 + "&phrase=&any_of_words=&none_of_words=&group=0&from_day="
			+ numbers_to_date(1, m_month, 2016, ".") + "&to_day="
			+ numbers_to_date(all_days, m_month, 2016, ".") + "&sort_by=desc";
		if (!get_connect(prefix + to_str(1) + sufix)) exit(0);
		ina_single_row(m_raw);
		SUM = pull_number<int>(convert_encoding(boost::regex_replace(m_raw,
			boost::regex(R"#(<div class="search_res_info">.*?</form>.*?</b>(.*?)<div class=\"search_h_line\">)#"),
			"$1", boost::regex_constants::format_no_copy),
			"UTF-8", "CP1251"));
		m_raw.clear();
		SUM_first_link = sum_first_link(SUM, limit);
		for (unsigned int i = 1; i < SUM_first_link; i++)
			walk_on_links(prefix + to_str(i) + sufix);
		m_raw += temp;

		m_setlink = pull_unit(m_raw,
			R"#(<div class="rubric_item search_item">.*?<a\s+href=\"http://www\.belta\.by([\w|/|-]+)\"\s+class=\"rubric_item_title\")#", "$1\n",
			R"#(/(\w+)/.*?/)#", "$1");
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "sputnik-georgia.ru")
	{
		limit = 100;
		link = "/services/search/getmore/?search_area=title&query%5B%5D="
			+ quer0 + "&limit=" + to_str(limit) + "&offset=" + to_str(0) + "&sort=date&interval=period&date_from="
			+ numbers_to_date(2016, m_month, 1, "-") + "&date_to="
			+ numbers_to_date(2016, m_month, all_days, "-");
		if (!get_connect(link)) exit(0);
		m_setlink = pull_unit(m_raw, R"#(<h2 class=\"b-plainlist__title\"><a href=\"(.*?)\">)#", "$1\n");
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "newsru.co.il")
	{
		link = "/search.html?qry=%F3%EA%F0%E0%E8%ED%E0&tpc=2&d1d=01&d1m=0" + to_str(m_month) + "&d1y=2016&d2d=" + to_str(all_days)
			+ "&d2m=0" + to_str(m_month) + "&d2y=2016&sort=2";
		if (!get_connect(link)) exit(0);
		m_setlink = pull_unit(m_raw, R"#(<div class=\"item\".*?\"><a href=\"(.*?)\" class=\"img\")#", "$1\n");
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "tengrinews.kz")
	{
		link = "/search/?text=%D1%83%D0%BA%D1%80%D0%B0%D0%B8%D0%BD%D0%B0&type_search=tn&searchid=1830602&sort=date-sdate%3Ad&cx=005730441761741791705%3Awe7eyweiqe4&x=0&y=0";
		if (!get_connect(link)) exit(0);
		ina_single_row(m_raw);
		boost::regex re(R"#(<div class=\"search-result\">.*?<span>(.*?)</span>.*?<div class=\"search-result-name\">\s*<a href=\"(.*?)\"\s)#");
		m_raw = boost::regex_replace(m_raw, re, "$1###$2###\n", boost::regex_constants::format_no_copy);
		std::istringstream iss(m_raw);
		re = R"#(\d+\.(\d+)\.(\d+) [\d,\:]+\#\#\#(.*?)\#\#\#)#";
		std::string temp;
		while (getline(iss, temp))
			if (
				boost::regex_replace(temp, re, "$1", boost::regex_constants::format_no_copy) == month() &&
				boost::regex_replace(temp, re, "$2", boost::regex_constants::format_no_copy) == "2016"
				)
				m_setlink.insert(boost::regex_replace(temp, re, "$3", boost::regex_constants::format_no_copy));
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "www.vb.kg")
	{
		link = "/?sort_by=&search=" + quer0;
		if (!get_connect(link)) exit(0);
		boost::regex re(R"#(<span class=\"topic_time_create\">\d+\.(\d+)\.(\d+)</span>\s*<.*?><a href=\"http://www\.vb\.kg(.*?)\">)#");
		m_raw = boost::regex_replace(m_raw, re, "$1:::::$2:::::$3:::::\n", boost::regex_constants::format_no_copy);
		std::istringstream iss(m_raw);
		re = R"#((\d+):::::(\d+):::::(.*?):::::)#";
		std::string temp;
		while (getline(iss, temp))
			if (boost::regex_replace(temp, re, "$1", boost::regex_constants::format_no_copy) == "08" &&
				boost::regex_replace(temp, re, "$2", boost::regex_constants::format_no_copy) == "2016")
				m_setlink.insert(boost::regex_replace(temp, re, "$3", boost::regex_constants::format_no_copy));
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else if (m_host == "point.md")
	{
		link = "/ru/novosti/poisk?keyword=" + quer0;
		if (!get_connect(link)) exit(0);
		ina_single_rowconv(m_raw);
		boost::regex re(R"#(<h2 class=\".*?><.*?href=\"(.*?)\">.*?<time class=\".*?>(.*?)</time>)#");
		m_raw = boost::regex_replace(m_raw, re, "$2###$1###\n", boost::regex_constants::format_no_copy);

		std::istringstream iss(m_raw);
		re = R"#(\d+\s+(\w+)\s+(\d+)\,\s+[\d,:]+\#\#\#(.*?)\#\#\#)#";
		std::string temp;
		while (getline(iss, temp))
			if (boost::regex_replace(temp, re, "$1", boost::regex_constants::format_no_copy) == month("word") &&
				boost::regex_replace(temp, re, "$2", boost::regex_constants::format_no_copy) == "2016")
				m_setlink.insert(boost::regex_replace(temp, re, "$3", boost::regex_constants::format_no_copy));
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
		{
			std::cout << "	--- " << count++ << " ---\n";
			dataFromSite dfs = get_data(*it,
				R"#()#", "$1.$2.$3", "2", "3",	// pdate
				R"#()#",	// country
				R"#()#",	// publisher
				R"#()#",	// link
				R"#()#",	// title
				R"#()#",	// subtitle
				R"#()#");	// body
			if (dfs.body.size() != 0 && dfs.country.size() != 0 &&
				(dfs.nameAther.size() != 0 || dfs.nameUA.size() != 0)
				&& dfs.publisher.size() != 0)
			{
				m_data.push_back(dfs);
				save_to_file(nfile, dfs);
				//save_report(dfs);
			}
			system("cls");
			if (count == 50) break;
		}
	}
	else throw std::exception("Unknown host!!!");

	/*
	std::ofstream outf("d:/777.txt");
	for (auto it = m_setlink.begin(); it != m_setlink.end(); ++it)
	outf << m_port << "://" << m_host << *it << std::endl;
	*/
}
size_t parsingSites::size_setlink()
{
	return m_setlink.size();
}
void parsingSites::save_to_file(std::string nfile, const dataFromSite & df)
{
	std::ofstream out(nfile.c_str(), std::ofstream::out | std::ofstream::app);
	out << df.country << '\t'
		<< df.publisher << '\t'
		//<< part_body_tofile(df.body) << '\t'
		<< df.body << '\t'
		<< df.link << '\t'
		<< df.category << '\t';
	if (df.nameUA.size() != 0)
		for (auto pt = df.nameUA.begin(); pt != df.nameUA.end(); ++pt)
			if (pt != --(df.nameUA.end()) || df.nameAther.size() != 0)
				out << *pt << ", ";
			else out << *pt;
			if (df.nameAther.size() != 0)
				for (auto pt = df.nameAther.begin(); pt != df.nameAther.end(); ++pt)
					if (pt != --(df.nameAther.end()))
						out << *pt << ", ";
					else out << *pt;
					out << '\t' << df.tonality << std::endl;
}
void parsingSites::save_report(const dataFromSite & df, const std::string & nfile)
{
	//std::string nfile("d:\\INFO_MONTH\\reports\\info_descript_" + convert_month(m_month) + "_2016.txt");
	std::ofstream out(nfile.c_str(), std::ofstream::out | std::ofstream::app);
	out << df.country << '\t'
		<< df.publisher << '\t'
		//<< part_body_tofile(df.body) << '\t'
		<< df.body << '\t'
		<< df.link << '\t'
		<< df.category << '\t';
	if (df.nameUA.size() != 0)
	{
		for (auto pt = df.nameUA.begin(); pt != df.nameUA.end(); ++pt)
			if (pt != --(df.nameUA.end()) || df.nameAther.size() != 0)
				out << *pt << ", ";
			else out << *pt;
	}
	if (df.nameAther.size() != 0)
	{
		for (auto pt = df.nameAther.begin(); pt != df.nameAther.end(); ++pt)
		{
			if (pt != --(df.nameAther.end()))
				out << *pt << ", ";
			else out << *pt;
		}
	}
	out << '\t' << df.tonality << std::endl;
	/*
	nfile = "d:\\INFO_MONTH\\reports\\info_descript_" + convert_month(m_month) + "_2016.xls.txt";
	std::ofstream out3(nfile.c_str(), std::ofstream::out | std::ofstream::app);
	out3 << df.country << '\t'
	<< df.publisher << '\t'
	<< part_body_tofile(df.body) << '\t'
	<< df.link << '\t'
	<< df.category << '\t'
	<< df.tonality << '\t';
	if (df.nameUA.size() != 0)
	{
	for (auto pt = df.nameUA.begin(); pt != df.nameUA.end(); ++pt)
	if (pt != --(df.nameUA.end()) || df.nameAther.size() != 0)
	out3 << *pt << "\n\t\t\t\t\t\t";
	else  out3 << *pt;
	}
	if (df.nameAther.size() != 0)
	{
	for (auto pt = df.nameAther.begin(); pt != df.nameAther.end(); ++pt)
	if (pt != --(df.nameAther.end())) out3 << *pt << "\n\t\t\t\t\t\t";
	else  out3 << *pt;
	}
	out3 << std::endl;
	*/
}
