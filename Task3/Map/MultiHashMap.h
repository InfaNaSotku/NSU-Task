#pragma once
#include"Map.h"
namespace MapSpace
{
	template<class K, class V>
	class MultiHashMap : public Map<K, V>
	{
	public:
		class Array
		{
		private:
			MultiHashMap* ptr_;
			K key_;
		public:
			Array(MultiHashMap* ptr, K key) : ptr_(ptr), key_(key) {}
			V& operator[](size_t pos);
		};
	public:
		Map<K, V>& Add(K key, V val) override;
		Map<K, V>& Delete(K key) override;
		size_t SizeK(K key);
		Array GetK(K key) { return Array(this, key); }
	};
	template<class K, class V>
	Map<K, V>& MultiHashMap<K, V>::Add(K key, V val)
	{
		size_t k_hash = this->GetHash(key);
		if (this->array_size_ <= k_hash || double(this->element_counts_ / this->array_size_) * 100 >= this->max_occupancy_)
			this->resize(max(this->element_counts_ + 1, k_hash));
		size_t pos = this->find(key);
		this->element_counts_++;
		while (pos < this->array_size_ && this->data_ptr_[pos].fill_flag_)
			pos++;
		if (pos == this->array_size_)//not empty space
		{
			throw exception("Space is ended");
		}
		this->data_ptr_[pos].fill_flag_ = true;
		this->data_ptr_[pos].key_ = key;
		this->data_ptr_[pos].val_ = val;
		return *this;
	}
	template<class K, class V>
	Map<K, V>& MultiHashMap<K, V>::Delete(K key)
	{
		size_t pos = this->find(key);
		this->element_counts_--;
		while (pos != this->array_size_ && this->data_ptr_[pos].key_ == key)
		{
			size_t shift = pos;
			while (this->array_size_ > shift + 1 &&
				this->data_ptr_[shift].fill_flag_ &&
				this->GetHash(this->data_ptr_[shift + 1].key_) != shift + 1)//move elements left if needed
			{
				this->data_ptr_[shift] = this->data_ptr_[shift + 1];
				shift++;
			}
			this->data_ptr_[shift].fill_flag_ = false;
			this->data_ptr_[shift].key_ = K();
			this->data_ptr_[shift].val_ = V();
		}
		return *this;
	}
	template<class K, class V>
	size_t MultiHashMap<K, V>::SizeK(K key)
	{
		size_t pos = this->find(key);
		size_t count = 0;
		while (pos != this->array_size_ && this->data_ptr_[pos].key_ == key)
		{
			pos++;
			count++;
		}
		return count;
	}
	template<class K, class V>
	V& MultiHashMap<K, V>::Array::operator[](size_t pos)
	{
		size_t i = this->ptr_->GetHash(this->key_);
		while (pos > 0 && i < this->ptr_->array_size_ && this->ptr_->data_ptr_[i].key_ == this->key_)
		{
			i++;
			if (i >= this->ptr_->array_size_ || this->ptr_->data_ptr_[i].key_ != this->key_)
				break;
			pos--;
		}
		if (pos > 0)
			throw exception("out of bounds array");
		else
			return this->ptr_->data_ptr_[i].val_;
	}
}
