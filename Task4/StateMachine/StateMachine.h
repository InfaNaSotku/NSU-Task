#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<unordered_map>
#include<map>
#include<set>
#include<queue>
using std::set;
using std::vector;
using std::string;
using std::unordered_map;
using std::exception;
using std::endl;
using std::pair;
using std::queue;
using std::map;
using std::ostream;
//#define DEBUGDETERMINISE
namespace StateMachine
{
	class Machine
	{
	private:
		class Node
		{
		public:
			enum class ConditionType
			{
				pDEFAULT,
				pINITIAL,
			};
		public:
			class Transition
			{
			public:
				Node* cond_;
				char val_;
			public:
				Transition() : cond_(nullptr), val_(NULL) {}
				Transition(Node* condition, char val) : cond_(condition), val_(val) {}
				~Transition() {}
			};
		public:
			vector<Transition> trans_list_;//contains machine transition 
			ConditionType c_type_;//Condition type
			size_t number_;
			bool final_flag_;
		public:
			Node() = delete;
			Node(size_t number) : c_type_(ConditionType::pDEFAULT), trans_list_(NULL), 
				final_flag_(false), number_(number) {}
			bool CheckRecognizability(string str);
			static vector<Transition> UniteTransitionList(const vector<Transition>& first, const vector<Transition>& second);
		};
	public:
		enum class MachineType
		{
			pDETERMENISTIC,
			pNONEDETERMENISTIC
		};
		enum class MachineUpdateTypeState
		{
			pSTATICAL,
			pDYNAMICAL
		};
	private:
		MachineType m_type_;
		vector<Node*> cond_list_;//contains condition
		unordered_map<char, bool> alphabet_;
		MachineUpdateTypeState state_;/*when =pDYNAMICAL allows to have information of machine type
		but requires more resources
		*/
	private:
		void UpdateType();
	public:
		MachineType GetMachineType();
		void SetMachineUpdateTypeState(MachineUpdateTypeState state);
		Machine() : m_type_(MachineType::pDETERMENISTIC), cond_list_(NULL), alphabet_(NULL), 
			state_(MachineUpdateTypeState::pSTATICAL) {}
		Machine(MachineUpdateTypeState state) : Machine() { this->state_ = state; }
		Machine(size_t condition_count);
		Machine(size_t condition_count, MachineUpdateTypeState state) : 
			Machine(condition_count) { this->state_ = state; }
		Machine(const Machine& source) { *this = source; }
		~Machine();
		void UpdateTransition(size_t from, size_t to, char val);
		void SetInitialCondition(size_t condition_number);//initial condition is changeable
		void SetFinalCondition(size_t condition_number);
		bool CheckRecognizability(string str);
		bool CheckInitialCondition();
		void resize(size_t new_size);
		void print(ostream& out);
		Machine& operator=(const Machine& source);

		static Machine Determinise(Machine machine);
		static Machine parse(string str);//MachineState = Dynamical
	};

}