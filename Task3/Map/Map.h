#pragma once
#include<functional>
#include<math.h>
#include<algorithm>
using std::hash;
using std::exception;
using std::max;


namespace MapSpace
{
	constexpr size_t MAXOCCUPANCY = 80;//in percents
	constexpr size_t RESIZEOCCUPANCY = 50;//at the time of resize array will add as many plot as needed for occupancy was clear at ... percent
	constexpr size_t HASHCUT = 10007;//max hash rate, prime number better than common number//lazy tamplate
	template<class K, class V>
	struct Node//container object type
	{
		template<class K, class V>
			friend class Map;
		template<class K, class V>
			friend class HashMap;
		template<class K, class V>
			friend class MultiHashMap;
	protected:
		bool fill_flag_;//see occupancy of plot of in container
	public:
		K key_;
		V val_;
		Node() : val_(V()), fill_flag_(false), key_(K()) {}
	};
	template<class K, class V>
	class Map
	{
		using Node = Node<K, V>;
	protected:
		Node* data_ptr_;
		size_t array_size_;//the main size of array
		size_t element_counts_;//counts of elements in map
		size_t max_occupancy_;//in percents
		size_t find(K key);
		void resize(size_t needed_element_space);
		//size_t GetHash(K key) { return 1; }

		size_t GetHash(const K key) { return abs(int(hash<K>{}(key))) % max((int)HASHCUT, int(this->array_size_)); }
	public:
		class iterator
		{
		private:
			Map<K, V>* ptr_;
			size_t pos_;
		public:
			iterator(Map* ptr, const size_t pos) : ptr_(ptr), pos_(pos) {}
			iterator(const iterator& source) { *this = source; }
			iterator& operator=(const iterator& source);
			bool operator!=(const iterator& second);
			Node& operator*() { return this->ptr_->data_ptr_[this->pos_]; }
			iterator& operator++();
		};
	public:
		Map(const Map& source) : data_ptr_(nullptr), array_size_(NULL), element_counts_(NULL) { *this = source; }
		Map() : data_ptr_(nullptr), array_size_(NULL), element_counts_(NULL), max_occupancy_(MAXOCCUPANCY) {}
		Map(size_t max_occupancy) : data_ptr_(nullptr), array_size_(NULL), element_counts_(NULL), max_occupancy_(max_occupancy) { }
		~Map() { delete[] this->data_ptr_; }
		Map& operator=(const Map& source);
		V& Get(const K key);
		size_t size() { return this->element_counts_; }
		virtual Map& Add(K key, V val) = 0;
		virtual Map& Delete(K key) = 0;
		iterator begin();
		iterator end() { return Map<K, V>::iterator(this, this->array_size_); }
	};
	template<class K, class V>
	Map<K, V>& Map<K, V>::Map::operator=(const Map& source)
	{
		this->data_ptr_ = new Node[source.array_size_];
		this->array_size_ = source.array_size_;
		this->element_counts_ = source.element_counts_;
		for (size_t i = 0; i < source.array_size_; i++)
			this->data_ptr_[i] = source.data_ptr_[i];
		return *this;
	}
	template<class K, class V>
	V& Map<K, V>::Get(const K key)
	{
		size_t pos = this->find(key);
		if (pos != this->array_size_ && this->array_size_ && this->data_ptr_[pos].fill_flag_)
			return this->data_ptr_[pos].val_;
		else
			throw exception("element not founded");
	}
	template<class K, class V>
	void Map<K, V>::resize(size_t needed_element_space)
	{
		Node* temp_ptr = data_ptr_;
		size_t temp_array_size = this->array_size_;
		this->element_counts_ = 0;
		this->array_size_ = (size_t)ceil(needed_element_space * double(100 / RESIZEOCCUPANCY));
		this->data_ptr_ = new Node[this->array_size_];
		for (size_t i = 0; i < temp_array_size; i++)
		{
			if (temp_ptr[i].fill_flag_)
				this->Add(temp_ptr[i].key_, temp_ptr[i].val_);
		}
		delete[] temp_ptr;
	}
	template<class K, class V>
	size_t Map<K, V>::find(K key)
	{
		size_t i = this->GetHash(key);
		for (; i < this->array_size_; i++)
		{
			if (!this->data_ptr_[i].fill_flag_ || this->data_ptr_[i].key_ == key)
				return i;
		}
		return this->array_size_;
	}
	//iterator methods
	template<class K, class V>
	typename Map<K, V>::iterator& Map<K, V>::iterator::operator=(const iterator& source)
	{
		this->pos_ = source.pos_;
		this->ptr_ = source.ptr_;
		return *this;
	}
	template<class K, class V>
	typename Map<K, V>::iterator Map<K, V>::begin()
	{
		size_t pos = 0;
		while (pos < this->array_size_ && !this->data_ptr_[pos].fill_flag_)
			pos++;
		return Map<K, V>::iterator(this, pos);
	}
	template<class K, class V>
	typename Map<K, V>::iterator& Map<K, V>::iterator::operator++()
	{
		this->pos_++;
		while (this->pos_ < this->ptr_->array_size_ &&
			!this->ptr_->data_ptr_[this->pos_].fill_flag_)
			this->pos_++;
		return *this;
	}
	template<class K, class V>
	bool Map<K, V>::iterator::operator!=(const iterator& second)
	{
		if (this->pos_ != second.pos_ || this->ptr_ != second.ptr_)
			return true;
		else
			return false;
	}
}