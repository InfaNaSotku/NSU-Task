#pragma once
#include<functional>
#include<math.h>
#include<algorithm>
using std::hash;
using std::pair;
using std::exception;
using std::max;
namespace MapSpace
{
#define MAXOCCUPANCY 80//in percents
#define RESIZEOCCUPANCY 50//at the time of resize array will add as many plot as needed for occupancy was clear at ... percent
#define HASHCUT 10007//max hash rate, prime number better than common number
#define tmpl template<class K, class V>//lazy tamplate
	tmpl
		class Map
		{
		protected:
			struct _MyType//container object type
			{
				K key_;
				V val_;
				bool fill_flag_;//see occupancy of plot of in container
				_MyType() : val_(V()), fill_flag_(false) {}
			};
			_MyType* data_ptr_;
			size_t array_size_;//the main size of array
			size_t element_counts_;//counts of elements in map
			size_t max_occupancy_;//in percents
			size_t find(const K key);
			void resize(size_t needed_element_space);
			size_t GetHash(const K key) { return abs(int(hash<K>{}(key))) % max(HASHCUT, int(this->array_size_)); }
		public:
			Map(const Map& source) : data_ptr_(nullptr), array_size_(NULL), element_counts_(NULL) { *this = source; }
			Map() : data_ptr_(nullptr), array_size_(NULL), element_counts_(NULL), max_occupancy_(MAXOCCUPANCY) {}
			Map& operator=(const Map& source);
			V& Get(const K key);
			virtual Map& Add(const K key, const V val) = 0;
			virtual Map& Delete(const K key) = 0;
		}; 
	tmpl
		Map<K, V>& Map<K, V>::Map::operator=(const Map& source)
	{
		this->data_ptr_ = new _MyType[source.array_size_];
		this->array_size_ = source.array_size_;
		this->element_counts_ = source.element_counts_;
		for (size_t i = 0; i < source.array_size_; i++)
			this->data_ptr_[i] = source.data_ptr_[i];
		return *this;
	}
	tmpl
		V& Map<K, V>::Get(const K key)
	{
		size_t pos = this->find(key);
		if (pos != this->array_size_ && this->array_size_ && this->data_ptr_[pos].fill_flag_)
			return this->data_ptr_[pos].val_;
		else
			throw exception("element not founded");
	}
	tmpl
		void Map<K, V>::resize(size_t needed_element_space)
	{
		_MyType* temp_ptr = data_ptr_;
		size_t temp_array_size = this->array_size_;
		this->element_counts_ = 0;
		this->array_size_ = (size_t)ceil(needed_element_space * double(100 / RESIZEOCCUPANCY));
		this->data_ptr_ = new _MyType[this->array_size_];
		for (size_t i = 0; i < temp_array_size; i++)
		{
			if (temp_ptr[i].fill_flag_)
				this->Add(temp_ptr[i].key_, temp_ptr[i].val_);
		}
		delete[] temp_ptr;
	}
	tmpl
		size_t Map<K, V>::find(const K key)
	{
		size_t i = this->GetHash(key);
		for (; i < this->array_size_; i++)
		{
			if (!this->data_ptr_[i].fill_flag_ || this->data_ptr_[i].key_ == key)
				return i;
		}
		return this->array_size_;
	}
}
