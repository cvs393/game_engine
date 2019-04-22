#pragma once
//when using templates, we cannot do implementation in a 
//.cpp file, it must be in the header file

template <class T> 
struct pool 
{
	union mem_block
	{
	private:

		// Points to the next free item
		mem_block *next;
		// Storage of the item.
		T data;

	public:

		mem_block* memory;
		// Methods for the list of free items.
		mem_block *get_next_thing() const
		{
			return next;
		}
		void set_next_thing(mem_block *n)
		{
			next = n;
		}

		// this retrieves the storage space
		T *get_storage()
		{
			return reinterpret_cast<T *>(data);
		}

		void free(T *t) {
			// Destroy the object.
			t->T::~T();

			mem_block* new_pt = (mem_block*)t;
			new_pt->next = next->set_next_thing;
			next = new_pt;
		}
	};
};// pool<T>