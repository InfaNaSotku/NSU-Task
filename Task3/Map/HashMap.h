#pragma once
#include"Map.h"


namespace MapSpace
{
	tmpl
		class HashMap : public Map<K, V>
	{
	public:
		Map<K, V>& Add(const K key, const V val) override;
		Map<K, V>& Delete(const K key) override;
	};
	tmpl
		Map<K, V>& HashMap<K, V>::Add(const K key, const V val)
	{
		size_t k_hash = this->GetHash(key);
		if (this->array_size_ <= k_hash || double(this->element_counts_ / this->array_size_) * 100 >= this->max_occupancy_)
			this->resize(max(this->element_counts_ + 1, k_hash));
		size_t pos = this->find(key);
		this->element_counts_++;
		if (pos != this->array_size_)
		{
			this->data_ptr_[pos].fill_flag_ = true;
			this->data_ptr_[pos].key_ = key;
			this->data_ptr_[pos].val_ = val;
		}
		return *this;
	}
	tmpl
		Map<K, V>& HashMap<K, V>::Delete(const K key)
	{
		size_t pos = this->find(key);
		this->element_counts_--;
		if (pos != this->array_size_)
		{
			while (this->array_size_ > pos + 1 && this->data_ptr_[pos + 1].fill_flag_)
			{
				this->data_ptr_[pos] = this->data_ptr_[pos + 1];
				pos++;
			}
			this->data_ptr_[pos].fill_flag_ = false;
			this->data_ptr_[pos].key_ = NULL;
			this->data_ptr_[pos].val_ = V();
		}
		return *this;
	}
}