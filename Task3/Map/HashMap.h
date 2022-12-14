#pragma once
#include"Map.h"


namespace MapSpace {
	template<class K, class V>
		class HashMap : public Map<K, V>
	{
	public:
		Map<K, V>& Add(K key, V val) override;
		Map<K, V>& Delete(K key) override;
	};
	template<class K, class V>
		Map<K, V>& HashMap<K, V>::Add(K key, V val)
	{
		size_t k_hash = this->GetHash(key);
		if (this->array_size_ <= k_hash || double(this->element_counts_ / this->array_size_) * 100 >= this->max_occupancy_)
			this->resize(max(this->element_counts_ + 1, k_hash));
		size_t pos = this->find(key);
		if (pos == this->array_size_)//we need resize again
		{
			throw exception("Space is ended");
		}
		if (!this->data_ptr_[pos].fill_flag_)
			this->element_counts_++;
		this->data_ptr_[pos].fill_flag_ = true;
		this->data_ptr_[pos].key_ = key;
		this->data_ptr_[pos].val_ = val;
		return *this;
	}
	template<class K, class V>
		Map<K, V>& HashMap<K, V>::Delete(K key)
	{
		size_t pos = this->find(key);
		if (pos != this->array_size_ && this->data_ptr_[pos].fill_flag_)
		{
			this->element_counts_--;
			this->data_ptr_[pos].fill_flag_ = false;
			this->data_ptr_[pos].key_ = K();
			this->data_ptr_[pos].val_ = V();
			pos++;
			while (this->array_size_ > pos + 1 &&
				this->data_ptr_[pos].fill_flag_)//move elements left if needed
			{
				this->element_counts_--;
				K temp_key = this->data_ptr_[pos].key_;
				V temp_val = this->data_ptr_[pos].val_;
				this->data_ptr_[pos].fill_flag_ = false;
				this->data_ptr_[pos].key_ = K();
				this->data_ptr_[pos].val_ = V();
				this->Add(temp_key, temp_val);
				pos++;
			}
		}
		return *this;
	}
}