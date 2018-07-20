#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <boost/regex.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio.hpp>
#include <iconv.h>
struct dataFromSite {
	std::string pdate;
	std::string country;
	std::string publisher;
	std::string body;
	std::string link;
	std::set<std::string> pull_name;
	std::set<std::string> nameUA;
	std::set<std::string> nameAther;
	std::string category;
	std::string tonality;
};
template<typename T> std::string to_str(T x) {
	std::ostringstream oss;
	oss << x;
	return oss.str();
}
template<typename T> T to_number(std::string x) {
	std::istringstream iss(x);
	T n;
	iss >> n;
	return n;
}
template<typename T> T pull_number(std::string x) {
	std::string number;
	std::istringstream iss(x);
	char ch;
	iss.get(ch);
	while (!iss.eof())
	{
		if (isdigit(ch))
			number += ch;
		iss.get(ch);
	}

	return to_number<T>(number);
}
void timeDelay(size_t sec);
size_t sum_first_link(size_t sum, size_t lim);
std::string convert_encoding(const std::string& data, const std::string& from, const std::string& to);
std::set<std::string> pull_unit(const std::string & txt, const std::string & re, const std::string & ingoing,
	const std::string & re2 = R"#(/(\w+)/\w+/\w+\.html)#", const std::string & ingoing2 = "$1");
std::string convert_month(size_t month);
int days_in_month(size_t month);
std::string numbers_to_date(size_t x, size_t y, size_t z, const std::string & separator);
//std::set<std::string> name_for_matching(const std::string & body, const std::string & filename);
void name_for_matching(std::set<std::string> & ua, std::set<std::string> & ather);
void get_name(dataFromSite & df, const std::set<std::string> & nameUa, const std::set<std::string> & nameAth);
std::string part_body_tofile(const std::string & body, int sum = 1200);
class parsingSites
{
	void request_GET(std::ostream & rs, const std::string & lnk);
	bool answer(std::istream & ir);
	std::string save_answer(boost::asio::ip::tcp::socket & sock, boost::asio::streambuf & strbuf, std::istream & ir);
	std::string save_answer(boost::asio::ssl::stream<boost::asio::ip::tcp::socket> & sock, boost::asio::streambuf & strbuf, std::istream & ir);
	void walk_on_links(const std::string & lnk);
	void ina_single_row(std::string & str);
	void ina_single_rowconv(std::string & str);
public:
	parsingSites();
	parsingSites(const std::string & host, const std::string & port = "http", size_t month = 0);
	void create(const std::string & host, const std::string & port = "http", size_t month = 0);
	bool get_connect(const std::string & link);
	void get_dataFomSites(const std::string & query0, const std::string & query1,
		std::string nfile);
	std::string port();
	std::string host();
	std::string month(const std::string & label = "digit");
	size_t size_setlink();
	dataFromSite parsingSites::get_data(const std::string & link, const std::string & rdate,
		const std::string & ingoing_date, const std::string & ingoing_month, const std::string & ingoing_year,
		const std::string & rcountry, const std::string & rpublisher, const std::string & rlink, const std::string & rtitle,
		const std::string & rsubtitle, const std::string & rbody);
	void save_to_file(std::string nfile, const dataFromSite & df);
	void save_report(const dataFromSite & df, const std::string & nfile);
private:
	std::string m_raw;
	std::string m_port;
	std::string m_host;
	size_t m_month;
	std::set<std::string> m_setlink;
	std::vector<dataFromSite> m_data;
};