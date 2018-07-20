#include "declaration.h"
int main(int argc, char * argv[])
{
	// port == argv[1], host == argv[2], month == argv[3]

	// std::set<std::pair<std::string, std::string> > setraw;
	size_t month = to_number<size_t>(argv[3]);
	parsingSites site(argv[2], argv[1], month);
	std::string outfile("d:\\out_files\\raw_data_for_report.txt");
	
	//std::string outfile("d:\\out_files\\" + site.host() + "_" + argv[3] + "_month.txt");
	site.get_dataFomSites(
		"%D1%83%D0%BA%D1%80%D0%B0%D0%B8%D0%BD%D0%B0",
		"%D0%B0%D0%B2%D0%B0%D0%BA%D0%BE%D0%B2",
		outfile);
	std::cout << "Number all links: " << site.size_setlink() << std::endl;


	return 0;
}