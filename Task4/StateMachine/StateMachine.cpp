#include"StateMachine.h"
namespace StateMachine
{

	Machine::Machine(size_t condition_count) : m_type_(MachineType::pDETERMENISTIC),
		cond_list_(condition_count), state_(MachineUpdateTypeState::pSTATICAL) {
		for (size_t i = 0; i < condition_count; i++)
			this->cond_list_[i] = new Node(i);
		if (condition_count <= 0)
			throw exception("machine must have one condition at least");
	}
	Machine::~Machine()
	{
		for (size_t i = 0; i < this->cond_list_.size(); i++)
			delete this->cond_list_[i];
	}
	Machine& Machine::operator=(const Machine& source)
	{
		if (this == &source)
			return *this;
		this->state_ = source.state_;
		this->m_type_ = source.m_type_;
		this->resize(source.cond_list_.size());
		for (size_t i = 0; i < this->cond_list_.size(); i++)
		{
			this->cond_list_[i]->c_type_ = source.cond_list_[i]->c_type_;
			this->cond_list_[i]->final_flag_ = source.cond_list_[i]->final_flag_;
		}
		for (size_t i = 0; i < this->cond_list_.size(); i++)
		{
			this->cond_list_[i]->trans_list_.resize(source.cond_list_[i]->trans_list_.size());
			for (size_t j = 0; j < this->cond_list_[i]->trans_list_.size(); j++)
			{
				size_t to = source.cond_list_[i]->trans_list_[j].cond_->number_;
				char val = source.cond_list_[i]->trans_list_[j].val_;
				this->cond_list_[i]->trans_list_[j] = Node::Transition(this->cond_list_[to], val);//i == from
			}
		}
		this->alphabet_ = source.alphabet_;
		return *this;
	}

	void Machine::UpdateType()
	{
		//1)
		/*
		    transition list must have all the word from alphabet
			and machine can to have only one transition for each word
			for determenistic machine
		*/
		for (size_t i = 0; i < this->cond_list_.size(); i++)
		{
			bool flag = true;
			for (auto& word_it : this->alphabet_)
			{
				bool word_a = false;//word availibility
				bool word_r = false;//flag of word repeat
				char word = word_it.first;
				unordered_map<char, bool> heap;
				for (size_t j = 0; j < this->cond_list_[i]->trans_list_.size(); j++)
				{
					if (this->cond_list_[i]->trans_list_[j].val_ == word)
						word_a = true;
					if (heap[this->cond_list_[i]->trans_list_[j].val_])
					{
						word_r = true;
						break;
					}
					heap[this->cond_list_[i]->trans_list_[j].val_] = true;
				}
				if (word_r || !word_a)
				{
					flag = false;
					break;
				}
			}
			if (!flag)
			{
				this->m_type_ = Machine::MachineType::pNONEDETERMENISTIC;
				return;
			}
		}
		this->m_type_ = MachineType::pDETERMENISTIC;
		//2)
		/*
		    we must can to reach every condition in machine
			for deterministic automat
		*/
		set<size_t> heap;
		for (size_t i = 0; i < this->cond_list_.size(); i++)
		{
			if (this->cond_list_[i]->c_type_ == Node::ConditionType::pINITIAL)
				heap.emplace(i);
			for (size_t j = 0; j < this->cond_list_[i]->trans_list_.size(); j++)
			{
				if(this->cond_list_[i]->trans_list_[j].cond_->number_ != 
					this->cond_list_[i]->number_)//transition into themselves do not count
					heap.emplace(this->cond_list_[i]->trans_list_[j].cond_->number_);
			}
		}
		if (heap.size() != this->cond_list_.size())
			this->m_type_ = MachineType::pNONEDETERMENISTIC;
		//
	}
	vector<Machine::Node::Transition> Machine::Node::UniteTransitionList(const vector<Transition>& first, const vector<Transition>& second)
	{
		vector<Transition> rez = first;
		bool used_flag = false;
		for (size_t j = 0; j < second.size(); j++)
		{
			for (size_t i = 0; i < first.size(); i++)
				if (first[i].cond_->number_ == second[j].cond_->number_ &&
					first[i].val_ == second[j].val_)
				{
					used_flag = true;
					break;
				}
			if(!used_flag)
				rez.push_back(second[j]);
		}
		return rez;
	}
	bool Machine::CheckInitialCondition()
	{
		bool initial_flag = false;
		for (Node*& node : this->cond_list_)
			if (node->c_type_ == Node::ConditionType::pINITIAL)
			{
				initial_flag = true;
				break;
			}
		return initial_flag;
	}

	void Machine::print(ostream& out)
	{
		auto print_cond_number = [](Node* cond, ostream& out) -> void
		{
			if (cond->c_type_ == Node::ConditionType::pINITIAL)
				out << '(';
			if (cond->final_flag_)
				out << '[';
			out << cond->number_;
			if (cond->final_flag_)
				out << ']';
			if (cond->c_type_ == Node::ConditionType::pINITIAL)
				out << ')';
		};
		for (size_t i = 0; i < this->cond_list_.size(); i++)
		{
			for (size_t j = 0; j < this->cond_list_[i]->trans_list_.size(); j++)
			{
				print_cond_number(this->cond_list_[i], out);
				out << ' ';
				print_cond_number(this->cond_list_[i]->trans_list_[j].cond_, out);
				out << ' ';
				out << this->cond_list_[i]->trans_list_[j].val_ << endl;

			}
			if(!this->cond_list_[i]->trans_list_.empty())
				out << endl;
		}
	}
	void Machine::resize(size_t new_size)
	{
		size_t size = this->cond_list_.size();
		this->cond_list_.resize(new_size);
		for (size_t i = size; i < this->cond_list_.size(); i++)
			this->cond_list_[i] = new Node(i);
	}
	void Machine::UpdateTransition(size_t from, size_t to, char val)
	{
		if (from >= this->cond_list_.size() || to >= this->cond_list_.size())
			throw exception("condition out of range");
		bool initial_flag = false;
		if(!this->CheckInitialCondition())
			throw exception("Machine must have initial condition");
		alphabet_[val] = true;
		this->cond_list_[from]->trans_list_ = Node::UniteTransitionList(this->cond_list_[from]->trans_list_,
			vector<Node::Transition>(1, Node::Transition(this->cond_list_[to], val)));
		if(this->state_ == MachineUpdateTypeState::pDYNAMICAL)
			this->UpdateType();
	}
	
	void Machine::SetInitialCondition(size_t condition_number)
	{
		if (condition_number >= this->cond_list_.size())
			throw exception("condition out of range");
		for (Node*& node : this->cond_list_)
			if (node->c_type_ == Node::ConditionType::pINITIAL)
			{
				node->c_type_ = Node::ConditionType::pDEFAULT;
				break;
			}
		this->cond_list_[condition_number]->c_type_ = Node::ConditionType::pINITIAL;
	}
	void Machine::SetFinalCondition(size_t condition_number)
	{
		if (condition_number >= this->cond_list_.size())
			throw exception("condition out of range");
		this->cond_list_[condition_number]->final_flag_ = true;
	}
	
	bool Machine::Node::CheckRecognizability(string str)
	{
		if (str.empty())
			return this->final_flag_;
		for (Transition& transition : this->trans_list_)
			if(transition.val_ == str[0])
				if (transition.cond_->CheckRecognizability(str.substr(1, str.size() - 1)))
					return true;
		return false;
	}
	bool Machine::CheckRecognizability(string str)
	{
		if (!this->CheckInitialCondition())
			throw exception("Machine must have initial condition");
		for (Node*& node : this->cond_list_)
			if (node->c_type_ == Node::ConditionType::pINITIAL)
			{
				return node->CheckRecognizability(str);
			}
	}

	Machine::MachineType Machine::GetMachineType()
	{
		if (this->state_ == MachineUpdateTypeState::pDYNAMICAL)
			return this->m_type_;
		else
			throw exception("Machine state is statical");
	}
	void Machine::SetMachineUpdateTypeState(MachineUpdateTypeState state)
	{
		if (!this->CheckInitialCondition())
			throw exception("Machine must have initial condition");
		if (state == MachineUpdateTypeState::pSTATICAL)
			this->UpdateType();
		this->state_ = state;
	}

	Machine Machine::Determinise(Machine machine)
	{
		if (machine.state_ == MachineUpdateTypeState::pDYNAMICAL &&
			machine.m_type_ == MachineType::pDETERMENISTIC)
			return machine;
		if (!machine.CheckInitialCondition())
			throw exception("Machine must have initial condition");
		Machine m;
		//finds initial condition
		size_t in_c_pos;
		for (Node*& node : machine.cond_list_)
			if (node->c_type_ == Node::ConditionType::pINITIAL)
			{
				in_c_pos = node->number_;
				break;
			}
		queue<pair<vector<size_t>, char>> q_set;//vector<size_t> - set of condition of initial machine/condition in new machine
		//initial condition starts algorithm
		for (auto& word : machine.alphabet_)
			q_set.push(pair<vector<size_t>, char>(vector<size_t>(1, in_c_pos), word.first));

		//helps function
		auto vector_equal = [](vector<size_t>& f, vector<size_t>& s) -> bool//given vector without repeat here
		{
			unordered_map<size_t, size_t> used;
			for (size_t i = 0; i < f.size(); i++)
			{
				used[f[i]]++;
			}
			for (size_t i = 0; i < s.size(); i++)
			{
				used[s[i]]++;
			}
			for (auto& it : used)
				if (it.second == 1)
					return false;
			return true;
		};
		auto find_set = [vector_equal](vector<vector<size_t>> f, vector<size_t> source) ->size_t
		{
			for (size_t i = 0; i < f.size(); i++)
			{
				if (vector_equal(f[i], source))
					return i;
			}
			return f.size();
		};
		auto vector_cleaner = [](vector<size_t>& f) -> void//removes repeat in vector
		{
			map<size_t, bool> used;
			for (size_t i = 0; i < f.size(); i++)
			{
				used[f[i]] = true;
			}
			vector<size_t> rez;
			for (auto& it : used)
				rez.push_back(it.first);
			f = rez;
		};
		
		//
		unordered_map<size_t, vector<pair<vector<size_t>, char>>> used_list;//key show to position in node_list
		vector<vector<size_t>> node_list;//for used_list
		node_list.push_back(vector<size_t>(1, in_c_pos));
		while (!q_set.empty())
		{
			pair<vector<size_t>, char> cur_trans = q_set.front();
			size_t cur_transe_pos = find_set(node_list, cur_trans.first);
			q_set.pop();
			vector<size_t> new_set;
			for (size_t i = 0; i < cur_trans.first.size(); i++)
			{
				size_t cur_node_number = cur_trans.first[i];
				//we should find all transtion of cur_trans.first[i] codition on cur_trans.second word
				for (size_t j = 0; j < machine.cond_list_[cur_node_number]->trans_list_.size(); j++)
				{
					if (machine.cond_list_[cur_node_number]->trans_list_[j].val_ == cur_trans.second)
						new_set.push_back(machine.cond_list_[cur_node_number]->trans_list_[j].cond_->number_);
				}
			}

			//new set complete, clearing him
			vector_cleaner(new_set);


			size_t pos = find_set(node_list, new_set);
			if (pos == node_list.size())//didn't find set
				if (!new_set.empty())
				{
					for (auto& word : machine.alphabet_)
						q_set.push(pair<vector<size_t>, char>(new_set, word.first));
					node_list.push_back(new_set);
				}
			if(!new_set.empty())
			    used_list[cur_transe_pos].push_back(pair<vector<size_t>, char>(new_set, cur_trans.second));
			//new node created
		}

#ifdef DEBUGDETERMINISE
		for (auto& it : used_list)
		{
			cout << "\x1b[32m" << '{';
			vector<size_t> set = node_list[it.first];
			for (size_t i = 0; i < set.size(); i++)
			{
				cout << set[i];
				if (i != set.size() - 1)
					cout << ' ';
				else
					cout << '}' << endl << "\x1b[37m";
			}
			for (size_t i = 0; i < it.second.size(); i++)
			{
				cout << it.second[i].second << ":{";
				for (size_t j = 0; j < it.second[i].first.size(); j++)
				{
					cout << it.second[i].first[j];
					if (j != it.second[i].first.size() - 1)
						cout << ',';
					else
						cout << '}' << endl;
				}
			}
		}
#endif // DEBUGDETERMINISE

		//fill out new machine
		m.resize(node_list.size());
		m.SetInitialCondition(0);
		m.SetMachineUpdateTypeState(MachineUpdateTypeState::pDYNAMICAL);
		m.alphabet_ = machine.alphabet_;
		for (size_t i = 0; i < node_list.size(); i++)
		{
			vector<pair<vector<size_t>, char>> trans_list = used_list[i];
			for (size_t j = 0; j < node_list[i].size(); j++)
			{
				size_t node_number = node_list[i][j];
				if (machine.cond_list_[node_number]->final_flag_)
				{
					m.SetFinalCondition(i);
					break;
				}
			}
			unordered_map<char, bool> dict;
			for (size_t j = 0; j < trans_list.size(); j++)
			{
				dict[trans_list[j].second] = true;
				size_t node_pos = find_set(node_list, trans_list[j].first);
				m.cond_list_[i]->trans_list_.push_back(Node::Transition(m.cond_list_[node_pos],
					trans_list[j].second));
			}
			bool empty_cond = false;
			for (auto& word : machine.alphabet_)
			{
				if (!dict[word.first])
				{
					if (empty_cond)
						m.UpdateTransition(i, m.cond_list_.size() - 1, word.first);
					else
					{
						m.resize(m.cond_list_.size() + 1);
						m.UpdateTransition(i, m.cond_list_.size() - 1, word.first);
						empty_cond = true;
					}
				}
			}
			if (empty_cond)
				for (auto& word : m.alphabet_)
					m.UpdateTransition(m.cond_list_.size() - 1, m.cond_list_.size() - 1, word.first);

		}
		return m;
	}
	Machine Machine::parse(string str)
	{
		Machine m(str.size() + 1);
		m.cond_list_[0]->c_type_ = Node::ConditionType::pINITIAL;
		for (size_t i = 0; i < str.size(); i++)
		{
			m.UpdateTransition(i, i + 1, str[i]);
			m.alphabet_[str[i]] = true;
		}
		m.cond_list_[str.size()]->final_flag_ = true;
		m.m_type_ = MachineType::pNONEDETERMENISTIC;
		m.state_ = MachineUpdateTypeState::pDYNAMICAL;
		return Machine::Determinise(m);
	}
}