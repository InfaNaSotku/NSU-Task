#pragma once
#include"Map.h"


namespace MapSpace
{
	tmpl
		class HashMap : public Map<K, V>
	{
	private:
		size_t Add(const K key) override;
	};
	tmpl
		size_t HashMap<K, V>::Add(const K key)
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
			return this->data_ptr_[pos].val_;
		}
		else
		{
			throw std::exception("Interrupt of Added(not enough space)");
		}
	}
}