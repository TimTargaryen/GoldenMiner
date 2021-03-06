template<typename T>
struct node {
	node* pred;//前驱
	T data;//数据域
	int rank;//秩(从0开始）
	node* succ;//后继
	node() {
		T new_one;
		succ = NULL; pred = NULL;
		rank = 0; data = new_one;//随机初始化
	};
	~node() {};
};//节点
template<typename T>
class List
{
	private:
		node<T>* header;//头哨兵
		node<T>* trailer;//尾哨兵
	public:
		int size;//大小
		List(int n = 0) {
			size = n;
			header = new node<T>; trailer = new node<T>;
			header->succ = trailer; trailer->pred = header;
			header->rank = -1; trailer->rank = -2;//虚秩
			node<T>* temp = NULL;
			node<T>* cntr = header;
			for (int i = 0; i < n; i++) {
				temp = new node<T>;
				temp->rank = i;
				cntr->succ = temp;
				temp->pred = cntr;
				cntr = temp;
			}
			cntr->succ = trailer;
			trailer->pred = cntr;
		}
		node<T>* at(int n) {
			node<T>* temp = header;
			while (temp->rank != n and temp->succ != NULL) temp = temp->succ;
			return temp;
		}//定位
		T& operator [](int n) { return at(n)->data; }//返回数据
		bool insert_pred(int n, T& e) {
			if (n >= size) return false;//非法插入
			node<T>* temp = at(n);
			node<T>* cntr = new node<T>;
			cntr->data = e; cntr->rank = n;
			cntr->succ = temp; cntr->pred = temp->pred;
			temp->pred->succ = cntr; temp->pred = cntr;
			while (cntr->succ != NULL) {
				cntr->rank += 1; cntr = cntr->succ;
			}
			trailer->rank = -2; size++;//扩容
			return true;
		}//前驱插入
		bool insert_succ(int n, T& e) {
			if (n >= size) return false;//非法插入
			node<T>* temp = at(n);
			node<T>* cntr = new node<T>;
			cntr->data = e; cntr->rank = n;
			cntr->pred = temp; cntr->succ = temp->succ;
			temp->succ->pred = cntr; temp->succ = cntr;
			while (cntr->succ != NULL) {
				cntr->rank += 1; cntr = cntr->succ;
			}
			trailer->rank = -2; size++;//扩容
			return true;
		}//后驱插入
		bool insert_front(T& e) { return insert_succ(-1, e); }
		bool insert_behind(T& e) { return insert_pred(-2, e); }
		bool remove(int n) {
			if (n >= size) return false;//非法删除
			node<T>* temp = at(n);
			node<T>* move = temp;
			temp->pred->succ = temp->succ;
			temp->succ->pred = temp->pred;
			while (move->succ != NULL) {
				move->rank -= 1; move = move->succ;
			}
			trailer->rank = -2; delete temp; 
			size--;//缩容
			return true;
		};
		~List() {
			for (int i = 0; i < size; i++) remove(i);
			delete header; delete trailer;
		};//析构	
};//链表类