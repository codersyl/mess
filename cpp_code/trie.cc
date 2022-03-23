// 字典树

// 方法一：二维数组
int N = 100009;
int trie[N][26];
int count[N];
int index = 0;

void insert(string s) {
	int p = 0;
	for(int i = 0; i < s.size(); i++) {
		int u = s[i] - 'a';
		if(trie[p][u] == 0)
			trie[p][u] = ++idx;
		p = trie[p][u]
	}
	count[p]++;
}

bool search(string s) {
	int p = 0;
	for(int i = 0; i < s.size(); i++) {
		int u = s[i] - 'a';
		if(trie[p][u] == 0)
			return false;
		p = trie[p][u]
	}
	return count[p] != 0;
}

bool startWith(string s) {
	int p = 0;
	for(int i = 0; i < s.size(); i++) {
		int u = s[i] - 'a';
		if(trie[p][u] == 0)
			return false;
		p = trie[p][u]
	}
	return true;
}