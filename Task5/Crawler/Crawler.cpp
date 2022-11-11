#include"Crawler.h"

namespace CrawlerSpace
{
	atomic<bool> Crawler::cr_state_(false);
	atomic<size_t> Crawler::visited_counts = 0;
    mutex Crawler::m_;
	
	void ParsePage(ifstream& page, vector<string>& list)
	{
		string protocol = "file";
		string searching_str = "<a href=\"" + protocol + "://";
		const size_t sear_str_size = searching_str.size();
		vector<size_t> p;
		string source;
		getline(page, source);
		calc_prefix_function(p, searching_str + "~" + source);
		for (size_t i = 0; i < p.size(); i++)
		{
			if (p[i] == searching_str.size())//verify string
			{
				size_t pos = i - sear_str_size;
				while (pos < source.size() && source[pos] != '\"')
					pos++;
				if (pos + 1 < source.size())
				{
					if (source[pos + 1] != '>')
						continue;
				}
				else
					continue;
				string new_str = source.substr(i - sear_str_size,
					pos - (i - sear_str_size));
				if (new_str.size() <= 6)
					continue;
				if (new_str.substr(new_str.size() - 5, 5) != ".html")
					continue;
				bool point = false;
				bool continue_flag = false;
				for (size_t i = 0; i < new_str.size(); i++)
				{
					if (new_str[i] == '.') 
					{
						if (point)
						{
							continue_flag = true;
							break;
						}
						else
						{
							point = true;
						}
					}
					if (new_str[i] > '9' && new_str[i] < '0' &&
						new_str[i] > 'z' && new_str[i] < 'a' &&
						new_str[i] > 'Z' && new_str[i] < 'A')
					{
						continue_flag = true;
						break;
					}
				}
				if (continue_flag)
					continue;
				list.push_back(new_str);
			}
		}
	}

	void Crawler::work(string input_folder, string output_folder, queue<string>& p_q, 
		map<string, bool>& passed_page, atomic<size_t>& running_workers_number)
	{
		bool running_state = true;
		while (running_workers_number.load(std::memory_order_seq_cst))
		{
			Crawler::m_.lock();
			if (p_q.empty())
			{
				Crawler::m_.unlock();
				if (running_state)
					running_workers_number.fetch_add(-1, std::memory_order_seq_cst);
				running_state = false;
			}
			else
			{
				if(!running_state)
					running_workers_number.fetch_add(1, std::memory_order_seq_cst);
				running_state = true;
				string cur_page = p_q.front();
				p_q.pop();
				Crawler::m_.unlock();
				vector<string> result;
				//parsing
				ifstream page;
				page.open(input_folder + "/" + cur_page);
				if (!page.good())
					throw exception("open file error");
				ParsePage(page, result);
				page.close();
				//parsing
				Crawler::visited_counts.fetch_add(1, std::memory_order_seq_cst);
				Crawler::m_.lock();
				for (auto& it : result)
				{
					if (!passed_page[it])
					{
						passed_page[it] = true;
						p_q.push(it);
						filesystem::copy(input_folder + "/" + it, output_folder);
					}
				} 
				Crawler::m_.unlock();
			}
		}
		
	}

	void Crawler::RunCrawler(size_t th_counts, string start_source, string input_folder, string output_folder)
	{
		this->work_time = 0;
		Crawler::visited_counts = 0;

		chrono::steady_clock::time_point start = chrono::steady_clock::now();
		filesystem::copy(input_folder + "/" + start_source, output_folder);

		if (Crawler::cr_state_.load(std::memory_order_seq_cst))
		{
			while (Crawler::cr_state_.load(std::memory_order_seq_cst));
			throw exception("Another crawler already run");
		}
		queue<string> p_q;//parse queue
		p_q.push(start_source);
		map<string, bool> passed_page;
		vector<thread> workers;
		atomic<size_t> running_workers_number = th_counts;
		passed_page[start_source] = true;
		Crawler::cr_state_.store(true, std::memory_order_seq_cst);
		for (size_t i = 0; i < th_counts; i++)
			workers.push_back(thread(this->work, input_folder, output_folder, ref(p_q), ref(passed_page), 
				ref(running_workers_number)));
		for (size_t i = 0; i < th_counts; i++)
			workers[i].join();
		Crawler::cr_state_.store(false, std::memory_order_seq_cst);
		chrono::steady_clock::time_point end = chrono::steady_clock::now();
		this->work_time = chrono::duration<long long, nano>(end-start).count()/1000000000.0;
	}

}