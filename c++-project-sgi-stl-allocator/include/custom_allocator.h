#pragma once

#include<mutex>
#include<stdexcept>

// һ���ռ������������ڷ������ڴ�
// ���� malloc() �� free() ��ʵ���ڴ�����������÷��� OOM ʱ�ͷ��ڴ�Ļص�����
template <int __inst>
class __malloc_alloc_template {

private:

	static void* _S_oom_malloc(size_t);
	static void* _S_oom_realloc(void*, size_t);
	static void (*__malloc_alloc_oom_handler)();

public:

	// �����ڴ�
	static void* allocate(size_t __n) {
		void* __result = malloc(__n);
		if (nullptr == __result) {
			// ����OOM��������
			__result = _S_oom_malloc(__n);
		}
		return __result;
	}

	// �ͷ��ڴ�
	static void deallocate(void* __p, size_t /* __n */) {
		free(__p);
	}

	// �ڴ��ط���
	static void* reallocate(void* __p, size_t /* old_sz */, size_t __new_sz) {
		void* __result = realloc(__p, __new_sz);
		if (nullptr == __result) {
			// ����OOM��������
			__result = _S_oom_realloc(__p, __new_sz);
		}
		return __result;
	}

	// �����µ�OOM�����������ؾɵĴ�����
	static void (*__set_malloc_handler(void (*__f)()))() {
		void (*__old)() = __malloc_alloc_oom_handler;
		__malloc_alloc_oom_handler = __f;
		return(__old);
	}

};

// ��ʼ���ྲ̬��Ա����
template <int __inst>
void (*__malloc_alloc_template<__inst>::__malloc_alloc_oom_handler)() = 0;

template <int __inst>
void* __malloc_alloc_template<__inst>::_S_oom_malloc(size_t __n) {
	void (*__my_malloc_handler)();
	void* __result;

	// ��ѭ��
	for (;;) {
		__my_malloc_handler = __malloc_alloc_oom_handler;
		if (nullptr == __my_malloc_handler) { throw std::bad_alloc(); }
		// ����OOM�ص�����
		(*__my_malloc_handler)();
		// �ٴγ��������ڴ�
		__result = malloc(__n);
		if (__result) return(__result);
	}
}

template <int __inst>
void* __malloc_alloc_template<__inst>::_S_oom_realloc(void* __p, size_t __n) {
	void (*__my_malloc_handler)();
	void* __result;

	// ��ѭ��
	for (;;) {
		__my_malloc_handler = __malloc_alloc_oom_handler;
		if (nullptr == __my_malloc_handler) { throw std::bad_alloc(); }
		// ����OOM�ص�����
		(*__my_malloc_handler)();
		// �ٴγ����ڴ��ط���
		__result = realloc(__p, __n);
		if (__result) return(__result);
	}
}

// �ض�������
typedef __malloc_alloc_template<0> malloc_alloc;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


// �����ռ������������ڷ���С���ڴ�
// ���û�����������ԭ����ڴ�ػ�����ʵ���ڴ����
template<typename T>
class __default_alloc_template {

public:

	// �ض�������
	using value_type = T;

	// ���캯��
	constexpr __default_alloc_template() noexcept {}

	// �������캯��
	constexpr __default_alloc_template(const __default_alloc_template&) noexcept = default;

	// ģ�幹�캯��
	template <class _Other>
	constexpr __default_alloc_template(const __default_alloc_template<_Other>&) noexcept {}

	// �����ڴ�ռ�
	T* allocate(size_t __n) {
		// �����ڴ�����ֽ���
		__n = __n * sizeof(T);

		void* __ret = nullptr;

		// �������ڴ�
		if (__n > (size_t)_MAX_BYTES) {
			__ret = malloc_alloc::allocate(__n);
		}
		// ����С���ڴ�
		else {
			// ��ȡ��Ӧ��С����������
			_Obj* volatile* __my_free_list = _S_free_list + _S_freelist_index(__n);

			// ��ȡ������
			std::lock_guard<std::mutex> __lock_instance(_mtx);

			// ��ȡ���������ͷ�ڵ�
			_Obj* __result = *__my_free_list;
			if (__result == nullptr)
				// ���ͷ�ڵ�Ϊ�գ���û�п��е��ڴ� chunk �飩��������µ� chunk ��
				__ret = _S_refill(_S_round_up(__n));
			else {
				// �����������ͷ�ڵ�ָ����һ���ڴ� chunk ��
				*__my_free_list = __result->_M_free_list_link;
				__ret = __result;
			}
		}
		
		return (T*)__ret;
	}

	// �ͷ��ڴ�ռ�
	void deallocate(void* __p, size_t __n) {
		// �ͷ��ڴ�����ֽ���
		__n = __n * sizeof(T);

		// ����ڴ�ֱ�ӽ���malloc�������ͷŵ�
		if (__n > (size_t)_MAX_BYTES) {
			malloc_alloc::deallocate(__p, __n);
		}
		// С���ڴ���յ���������
		else {
			// ��ȡ��Ӧ��С����������
			_Obj* volatile* __my_free_list = _S_free_list + _S_freelist_index(__n);
			_Obj* __q = (_Obj*)__p;

			// ��ȡ������
			std::lock_guard<std::mutex> __lock_instance(_mtx);

			// ���ͷŵ�С���ڴ���뵽��������ͷ����ͷ�巨��
			__q->_M_free_list_link = *__my_free_list;
			*__my_free_list = __q;
		}
	}

	// �ڴ������ / ����
	void* reallocate(void* __p, size_t __old_sz, size_t __new_sz) {
		void* __result;
		size_t __copy_sz;

		// ��һ����������¾ɴ�С����������ڴ�ش�����ֵ�ǣ�ֱ�ӵ���ϵͳ�� realloc()
		if (__old_sz > (size_t)_MAX_BYTES && __new_sz > (size_t)_MAX_BYTES) {
			return(realloc(__p, __new_sz));
		}

		// �ڶ�����������¾��ڴ�����ڴ���еĶ�����С��ȣ���ֱ�Ӹ��þ��ڴ��
		if (_S_round_up(__old_sz) == _S_round_up(__new_sz)) {
			return(__p);
		}

		// �������������Ҫִ���ڴ��ط���
		__result = allocate(__new_sz);	// �������ڴ�飨�����ڴ�ز��ԣ�
		__copy_sz = __new_sz > __old_sz ? __old_sz : __new_sz;	// ��ȫ������С��ȡ��Сֵ��
		memcpy(__result, __p, __copy_sz);	// ���ݿ�������������Ч���ݣ�
		deallocate(__p, __old_sz);	 // �ͷž��ڴ�飨���ݾ��ڴ��Ĵ�С���л��գ�

		return(__result);
	}

	// ������
	void construct(T * __p, const T & __val) {
		// ��ָ�����ڴ湹����󣨶�λ new��
		new(__p) T(__val); 
	}

	// ��������
	void destroy(T * __p) {
		// ��ָ�����ڴ���������
		__p->~T();
	}

private:

	enum { _ALIGN = 8 };            // �ڴ�������ȣ�ÿ�η��� 8 �ֽڵı�����
	enum { _MAX_BYTES = 128 };      // �����ռ���������������Χ��128 �ֽڣ�
	enum { _NFREELISTS = 16 };      // ������������������㷽ʽ��_MAX_BYTES / _ALIGN

	// ÿһ���ڴ� chunk ���ͷ��Ϣ
	union _Obj {
		union _Obj* _M_free_list_link;		// ��һ���ڴ� chunk ��ĵ�ַ
		char _M_client_data[1];				// ʵ�ʷ�����û����ڴ���ʼλ��
	};

	// ���������ڴ�ػ�����������ʵ�֣���Ҫ�����̰߳�ȫ���⣩
	static std::mutex _mtx;

	// ��¼�ڴ� chunk ��ķ������
	static char* _S_start_free;
	static char* _S_end_free;
	static size_t _S_heap_size;

	// ��֯����������������飬�����ÿһ��Ԫ�ص����Ͷ��� _Obj*
	static _Obj* volatile _S_free_list[_NFREELISTS];

	// �� __bytes �ϵ������ڽ��� 8 �ı�����ʵ���ڴ���룩
	static size_t _S_round_up(size_t __bytes) {
		return (((__bytes)+(size_t)_ALIGN - 1) & ~((size_t)_ALIGN - 1));
	}

	// ���� __bytes ��С�� chunk ��λ���������������е�����
	static size_t _S_freelist_index(size_t __bytes) {
		return (((__bytes)+(size_t)_ALIGN - 1) / (size_t)_ALIGN - 1);
	}

	// �����µ��ڴ� chunk �飬��������õ� chunk ��������ӣ���ӵ�����������
	void* _S_refill(size_t __n) {
		// һ���Է��� 20 ���ڴ� chunk ��
		int __nobjs = 20;
		char* __chunk = _S_chunk_alloc(__n, __nobjs);
		_Obj* volatile* __my_free_list;
		_Obj* __result;
		_Obj* __current_obj;
		_Obj* __next_obj;
		int __i;

		if (1 == __nobjs) {
			return(__chunk);
		}

		// ��ȡ��Ӧ��С����������
		__my_free_list = _S_free_list + _S_freelist_index(__n);

		// ���·�����ڴ� chunk ����ӵ���Ӧ������������
		__result = (_Obj*)__chunk;
		*__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
		for (__i = 1; ; __i++) {
			__current_obj = __next_obj;
			__next_obj = (_Obj*)((char*)__next_obj + __n);
			if (__nobjs - 1 == __i) {
				__current_obj->_M_free_list_link = 0;
				break;
			}
			else {
				__current_obj->_M_free_list_link = __next_obj;
			}
		}
		return(__result);
	}

	// ������Ӧ�ֽڴ�С���ڴ� chunk ��
	char* _S_chunk_alloc(size_t __size, int& __nobjs) {
		char* __result;
		size_t __total_bytes = __size * __nobjs;	// ������Ҫ��������ֽ���
		size_t __bytes_left = _S_end_free - _S_start_free;	// ��ȡ�ڴ��ʣ��ռ�

		// ��һ��������ڴ��ʣ��ռ���ȫ��������
		if (__bytes_left >= __total_bytes) {
			__result = _S_start_free;
			_S_start_free += __total_bytes;
			return(__result);
		}
		// �ڶ���������ڴ��ʣ��ռ䲻������ȫ�����󣬵������ܷ���һ�����ϵ��ڴ� chunk ��
		else if (__bytes_left >= __size) {
			__nobjs = (int)(__bytes_left / __size);
			__total_bytes = __size * __nobjs;
			__result = _S_start_free;
			_S_start_free += __total_bytes;
			return(__result);
		}
		// ������������ڴ��ʣ��ռ䲻��һ���ڴ� chunk ���С
		else {
			// ������Ҫ������ڴ�������2������ + ���������Ѵ�С��1/16�����϶��룩
			size_t __bytes_to_get = 2 * __total_bytes + _S_round_up(_S_heap_size >> 4);
			
			// ���������ڴ�ص�ʣ����Ƭ
			if (__bytes_left > 0) {
				// ��ȡ��Ӧ��С����������
				_Obj* volatile* __my_free_list = _S_free_list + _S_freelist_index(__bytes_left);
				// ��ʣ����Ƭ������������ͷ����ͷ�巨��
				((_Obj*)_S_start_free)->_M_free_list_link = *__my_free_list;
				*__my_free_list = (_Obj*)_S_start_free;
			}

			// �����µ��ڴ�鵽�ڴ��
			_S_start_free = (char*)malloc(__bytes_to_get);

			//  �µ��ڴ������ʧ�ܴ���
			if (nullptr == _S_start_free) {
				size_t __i;
				_Obj* volatile* __my_free_list;
				_Obj* __p;

				// ���ԴӸ�������������в��ҿ����ڴ��
				// ע�⣺�����Ը�С��������Ϊ�ڶദ�������������׵�������
				for (__i = __size;
					__i <= (size_t)_MAX_BYTES;
					__i += (size_t)_ALIGN) {
					__my_free_list = _S_free_list + _S_freelist_index(__i);
					__p = *__my_free_list;
					// �ҵ������ڴ��
					if (nullptr != __p) {
						*__my_free_list = __p->_M_free_list_link;
						_S_start_free = (char*)__p;
						_S_end_free = _S_start_free + __i;
						return(_S_chunk_alloc(__size, __nobjs));
						// ע�⣺�κ�ʣ����Ƭ���ջᱻ������ʵ���������
					}
				}

				// �������������޿����ڴ�ʱ��������ֶ�
				_S_end_free = 0;	// �쳣��ȫ����
				_S_start_free = (char*)malloc_alloc::allocate(__bytes_to_get);	// ʹ�ñ��÷�����ԣ������׳��쳣����ֹ����
				// �˴������������ܻ�ɹ���Ҫô�׳��쳣��Ҫô������⣩
			}

			// �����ڴ�ع������
			_S_heap_size += __bytes_to_get;	// �ۼƷ�����ڴ�����
			_S_end_free = _S_start_free + __bytes_to_get;	// �����µ��ڴ�ؽ���λ��

			// �ݹ�����������ڴ�������󣨴�ʱ�ڴ��������������ڴ�ռ䣩
			return(_S_chunk_alloc(__size, __nobjs));
		}
	}

};

// ��ʼ���ྲ̬��Ա����
template<typename T>
char* __default_alloc_template<T>::_S_start_free = nullptr;

template<typename T>
char* __default_alloc_template<T>::_S_end_free = nullptr;

template<typename T>
size_t __default_alloc_template<T>::_S_heap_size = 0;

template<typename T>
std::mutex __default_alloc_template<T>::_mtx;

template<typename T>
typename __default_alloc_template<T>::_Obj* volatile __default_alloc_template<T>::_S_free_list[_NFREELISTS] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
