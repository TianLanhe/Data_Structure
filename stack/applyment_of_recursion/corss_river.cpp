/*过河智力游戏
游戏规则：一家6口（爸爸、妈妈、两个女儿、两个儿子）及警察和小偷要从河这边渡到河对岸。
在河这边仅有一艘小舢板可以把他们载到对岸。可是，只有爸爸、妈妈和警察能够驾船，
不论成人与小孩，每程只能承载二人。在渡河过程中，你要避免以下三种情况的发生：
（1）	当警察与小偷分开时，小偷会伤害一家6口；
（2）	当爸爸看见妈妈离开时，爸爸便会教训女儿；
（3）	当妈妈看见爸爸离开时，妈妈便会教训儿子。
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

string from = "fmssddpt";
string to;
vector<string> result;

bool isThiefCanHurt(const string &str) {
	return str.find('t') != string::npos && str.find('p') == string::npos && str.size() > 1;
}

bool isOnlyFatherAndDaughter(const string &str) {
	return str.find('f') != string::npos && str.find('m') == string::npos
		&& str.find('d') != string::npos;
}

bool isOnlyMomAndSon(const string &str) {
	return str.find('f') == string::npos && str.find('m') != string::npos
		&& str.find('s') != string::npos;
}

bool canTogether(const string &vec) {
	return !isOnlyMomAndSon(vec) && !isOnlyFatherAndDaughter(vec) && !isThiefCanHurt(vec);
}

bool isNotLoop(const vector<string>& result) {
	vector<string>::size_type size = result.size();
	return size < 2 || result[size - 1] != result[size - 2] && result[size - 1] != string(result[size - 2].rbegin(), result[size - 2].rend());
}

bool corss(int direction) {
	if (from.empty()) {
		map<char, string> m;
		m['f'] = "父亲";
		m['m'] = "母亲";
		m['p'] = "警察";
		m['t'] = "小偷";
		m['s'] = "儿子";
		m['d'] = "女儿";
		int direction = 1;
		for (auto str : result) {
			cout << (direction ? "→" : "←");
			for (auto ch : str)
				cout << m[ch] << ' ';
			cout << endl;
			direction = 1 - direction;
		}
		return true;
	}
	else {
		string *ptrVec;
		string *ptrOther;
		if (direction == 0) {
			ptrVec = &from;
			ptrOther = &to;
		}
		else if (direction == 1) {
			ptrVec = &to;
			ptrOther = &from;
		}

		static char person[3] = { 'f','m','p' };
		string::size_type pos;
		int i;
		char temp;
		for (i = 0; i < 3; ++i) {
			if ((pos = ptrVec->find(person[i])) != string::npos) {
				ptrVec->erase(pos, 1);
				ptrOther->append(1, person[i]);

				// 一个人
				if (canTogether(*ptrVec) && canTogether(*ptrOther)) {
					result.push_back(string(1, person[i]));
					if (isNotLoop(result))
						if (corss(1 - direction))return true;
					result.pop_back();
				}

				// 两个人
				for (string::size_type j = 0; j != (*ptrVec).size(); ++j) {
					temp = (*ptrVec)[j];
					ptrVec->erase(j, 1);
					ptrOther->append(1, temp);

					if (canTogether(*ptrVec) && canTogether(*ptrOther)) {
						result.push_back(string(1, person[i]) + temp);
						if (isNotLoop(result))
							if (corss(1 - direction))return true;
						result.pop_back();
					}

					ptrOther->erase(ptrOther->size() - 1);
					ptrVec->insert(j, 1, temp);
				}

				ptrVec->insert(pos, 1, person[i]);
				ptrOther->erase(ptrOther->size() - 1);
			}
		}
		return false;
	}
}

int main() {
	corss(0);
	return 0;
}
