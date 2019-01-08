#include <time.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        char buf;
        vector<vector<char>> mmap(5);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cin >> buf;
                mmap[i].push_back(buf);
            }
        }
        int N;
        cin >> N;

        vector<string> vstrs;    //����� ������� �϶�淡 ����.
        map<string, bool> strs;  //�������� �ϼ��� �ܾ� �˻���

        map<char, map<pair<char, int>, bool>> status;  // status ���̵�
        // ���ٰ����� ������¿��� �������·� �Ѿ �� �ִ��� Ȯ���� �ؾ���.
        // ������ ���� �������̵��� ������
        // {�������,{{��������,���繮�ڿ� ����},������ ���ڿ���}}

        string str;  //�Է� ����
        for (int i = 0; i < N; i++) {
            cin >> str;
            strs[str] = false;
            vstrs.push_back(str);
            int j = 0;
            for (; j < str.size() - 1; j++) {
                //�߰����ڴ� true;
                status[str[j]][pair<char, int>(str[j + 1], j + 1)] = true;
            }
            //������ ���ڴ� false;
            status[str[j - 1]][pair<char, int>(str[j], j)] = false;
        }

        queue<pair<pair<int, int>, string>> que;  //������ǥ,������� �ϼ��� �ܾ�
        set<pair<pair<int, int>, string>> memo;   //ť�� �ߺ����� ������ �˻��

        // 25���� ����� �߿� �������̵��� �ִ� ���ڵ鸸 ť�� ����
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (status.find(mmap[i][j]) != status.end()) {
                    string tmp;
                    tmp += mmap[i][j];
                    que.push({{i, j}, tmp});
                }
            }
        }

        int dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        int di[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int ti, tj;

        while (!que.empty()) {
            auto front = que.front();
            que.pop();

            //ť�� ���Ծ����� �˻�
            if (memo.find(front) != memo.end()) continue;
            memo.insert(front);

            auto iter1 = status[mmap[front.first.first][front.first.second]];
            for (int i = 0; i < 8; i++) {
                ti = front.first.first + di[i];
                tj = front.first.second + dj[i];
                if (ti >= 0 and tj >= 0 and ti < 5 and tj < 5) {
                    //������ڿ��� �������ڷ� �̵��� �� �ִ��� �˻�
                    auto iter2 = iter1.find({mmap[ti][tj], front.second.size()});
                    if (iter2 != iter1.end()) {
                        //�������ڷ� �̵��� �� �ִٸ�....
                        if (iter2->second) {
                            // �������ڰ� ������ ���ڰ� �ƴѰ��
                            que.push({{ti, tj}, front.second + mmap[ti][tj]});
                            continue;
                        } else {
                            //�������ڰ� ������ �����ΰ��
                            auto ret = strs.find(front.second + mmap[ti][tj]);
                            if (ret != strs.end()) {
                                //���������� �ϼ��� �ܾ ���������� �˻�
                                ret->second = true;
                            }
                            continue;
                        }
                    }
                }
            }
        }
        //�Է��� ���� ������� �÷��׸� Ȯ���Ͽ� ���
        for (auto &iter : vstrs) {
            cout << iter << " " << (strs[iter] ? "YES" : "NO") << endl;
        }
    }

    return 0;
}