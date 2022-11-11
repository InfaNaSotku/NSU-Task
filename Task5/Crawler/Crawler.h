/*
my name is crawler and I was created with scotch and god's word, because I haven't multithreading primitives like "atomic operation
and variable" and CAS. I don't use lock-free structure and other. Because develope me with these things needs large time, 
but students don't have it, thank you:)
*/
#pragma once
#include<thread>
#include<chrono>
#include<filesystem>
#include<map>
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<atomic>
#include<mutex>
#include<string>
#include"../CMP/CMP.h"
using namespace std;
#define FILEPATH "files/"
namespace CrawlerSpace
{
	class Crawler
	{
	private:
		static mutex m_;
		static atomic<bool> cr_state_;//crawler state; true - in process; false - out process
		static void work(string output_folder, queue<string>& p_q, 
			map<string, bool>& passed_page, atomic<size_t>& running_workers_number);
		double work_time;
		static atomic<size_t> visited_counts;
	public:
		Crawler() : work_time(0) {}
		void RunCrawler(size_t th_counts, string start_source, string output_folder);//return time of crawler work in seconds
		void RunCrawler(string start_source, string output_folder) { this->RunCrawler(1, start_source, output_folder); }
		double GetTime() { return this->work_time; }
		static size_t GetVisitedCounts() { return Crawler::visited_counts.load(std::memory_order_seq_cst); }
	};

}