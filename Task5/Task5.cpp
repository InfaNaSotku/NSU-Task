#include"Crawler/Crawler.h"
#include<iomanip>
using namespace CrawlerSpace;
int main()
{
	Crawler cr;
	int thread_counts;
	string start_page;
	string input_folder;
	cin >> input_folder >> start_page >> thread_counts;
	cout << fixed << setprecision(3);
	cr.RunCrawler(thread_counts, start_page, input_folder, "output");
	cout << "completed for \x1b[32m" << cr.GetTime() << "\x1b[37m s." << endl;
	cout << "visited \x1b[33m" << cr.GetVisitedCounts() << "\x1b[37m pages";
}

