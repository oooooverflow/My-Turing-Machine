#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Turing {
	private:
		struct Node {
			string currentState;
			string nextState;
			string currentTape;
			string nextTape;
			string direction;
		};

		struct Tape {
			char ch;
			int index;
		};

		set<string> Q;
		set<char> S;
		set<char> G;
		string q0;
		string B;
		set<string> F;
		int N;
		vector<Node> Transition;

		vector<vector<Tape> > tapes;
		vector<vector<Tape>::iterator> heads;
		int step;
		string currentState;
		
		fstream f1, f2, f3;

	public:
		Turing(string temp) {
			step = 0;
			f2.open(temp+"/console.txt", ios::out);
			f3.open(temp+"/result.txt", ios::out);
		}
		
		~Turing() {
			f1.close();
			f2.close();
			f3.close();
		}
		void init(string input) {
			for(int i = 0; i < N; i++) {
				tapes[i].clear();
				heads[i] = tapes[i].begin();
			}
			step = 0;
			if(input.length() == 0) {
				Tape tape;
				tape.index = 0;
				tape.ch = B[0];
				tapes[0].push_back(tape);
			}
			else {
				for(int i = 0; i < input.length(); i++) {
					Tape tape;
					tape.index = i;
					tape.ch = input[i];
					tapes[0].push_back(tape);
				}	
			}
			heads[0] = tapes[0].begin();
			for(int i = 1; i < N; i++) {
				Tape tape;
				tape.index = 0;
				tape.ch = B[0];
				tapes[i].push_back(tape);
				heads[i] = tapes[i].begin();
			}
			currentState = q0;
		}

		void parser(string filename) {
			fstream f;
			f.open(filename, ios::in);
			/*if(f == NULL) {
				cout << filename << " not found" << endl;
				return;
			}*/
			string line, tmp;
			bool flag = false;
			string states;

			/* Q */
			while(getline(f, line)) {
				if(line.length() != 0 && line[0] != '\r' && line[0] != ';') {
					break;
				}
			}
			int index = 0;
			int end = 0;
			while(line[index] != '{') {
				index++;
			}
			index++;
			end = index;
			while(line[end] != '}') {
				end++;
			}
			states = line.substr(index, end-index);

			char *p;
			p = strtok((char*)(states.data()), ",");
			while(p != NULL) {
				tmp = p;
				Q.insert(tmp);
				p = strtok(NULL, ",");
			}

			/* S */
			while(getline(f, line)) {
				if(line.length() != 0 && line[0] != '\r' && line[0] != '\n' && line[0] != ';') {
					break;
				}
			}
			index = 0;
			while(line[index] != '{') {
				index++;
			}
			index++;
			end = index;
			while(line[end] != '}') {
				end++;
			}
			states = line.substr(index, end-index);
			p = strtok((char*)(states.data()), ",");
			while(p != NULL) {
				S.insert(p[0]);
				p = strtok(NULL, ",");
			}

			/* G */
			while(getline(f, line)) {
				if(line.length() != 0 && line[0] != '\r' && line[0] != '\n' && line[0] != ';') {
					break;
				}
			}
			index = 0;
			while(line[index] != '{') {
				index++;
			}
			index++;
			end = index;
			while(line[end] != '}') {
				end++;
			}
			states = line.substr(index, end-index);
			p = strtok((char*)(states.data()), ",");
			while(p != NULL) {
				G.insert(p[0]);
				p = strtok(NULL, ",");
			}

			/* q0 */
			while(getline(f, line)) {
				if(line.length() != 0 && line[0] != '\r' && line[0] != '\n' && line[0] != ';') {
					break;
				}
			}
			index = 0;
			while(line[index] != '=') {
				index++;
			}
			index += 2;
			end = index;
			while(end < line.length() && line[end] != ' ' && line[end] != ';') {
				end++;
			}
			if(line[end] == ' ' || line[end] == ';') {
				end--;
			}
			states = line.substr(index, end-index+1);
			q0 = states;

			/* B */
			while(getline(f, line)) {
				if(line.length() != 0 && line[0] != '\r' && line[0] != '\n' && line[0] != ';') {
					break;
				}
			}
			index = 0;
			while(line[index] != '=') {
				index++;
			}
			index += 2;
			end = index;
			while(end < line.length() && line[end] != ' ' && line[end] != ';') {
				end++;
			}
			if(line[end] == ' ' || line[end] == ';') {
				end--;
			}
			states = line.substr(index, end-index+1);
			B = states;

			/* F */
			while(getline(f, line)) {
				if(line.length() != 0 && line[0] != '\r' && line[0] != '\n' && line[0] != ';') {
					break;
				}
			}
			index = 0;
			while(line[index] != '{') {
				index++;
			}
			index++;
			end = index;
			while(line[end] != '}') {
				end++;
			}
			states = line.substr(index, end-index);
			states[states.length()-1] = ',';
			p = strtok((char*)(states.data()), ",");
			while(p != NULL) {
				tmp = p;
				F.insert(tmp);
				p = strtok(NULL, ",");
			}

			/* N */
			while(getline(f, line)) {
				if(line.length() != 0 && line[0] != '\r' && line[0] != '\n' && line[0] != ';') {
					break;
				}
			}
			index = 0;
			while(line[index] != '=') {
				index++;
			}
			index += 2;
			end = index;
			while(end < line.length() && line[end] != ' ' && line[end] != ';') {
				end++;
			}
			if(line[end] == ' ' || line[end] == ';') {
				end--;
			}
			states = line.substr(index, end-index+1);
			p = strtok((char*)(states.data()), " ");
			N = atoi(p);

			/* transition */
			index = 0;
			while(getline(f, line)) {
				if(line[0] == '\r' || line[0] == '\n' || line.length() == 0 || line[0] == ';') {
					continue;
				}
				end = 0;
				while(end < line.length() && (end == 0 || !(line[end] == ' ' && line[end-1] == ' '))) {
					end++;
				}
				states = line.substr(index, end-index+1);
				Node node;
				p = strtok((char*)(states.data()), " ");
				node.currentState = p;
				p = strtok(NULL, " ");
				node.currentTape = p;
				p = strtok(NULL, " ");
				node.nextTape = p;
				p = strtok(NULL, " ");
				node.direction = p;
				p = strtok(NULL, " ");
				node.nextState = p;
				Transition.push_back(node);
			}
			tapes.resize(N);
			heads.resize(N);
		}

		void printCurrent() {
			f2 << "Step" << "\t:\t" << step << endl;
			vector<Tape>::iterator it, it1, it2;
			for(int i = 0; i < N; i++) {
				for(it = tapes[i].begin(); it != tapes[i].end(); it++) {
					it1 = it;
					if((*it).ch != B[0] || it == heads[i]) {
						break;
					}
				}
				for(it = tapes[i].end()-1; it >= tapes[i].begin(); it--) {
					it2 = it;
					if((*it).ch != B[0] || it == heads[i]) {
						break;
					}
				}
				f2 << "Index" << i << "\t:";
				for(it = it1; it <= it2; it++) {
					f2 << "\t" << abs((*it).index);
				}
				f2 << endl;
				f2 << "Tape" << i << "\t:";
				for(it = it1; it <= it2; it++) {
					f2 << "\t" << (*it).ch;
				}
				f2 << endl;
				f2 << "Head" << i << "\t:";
				for(it = it1; it !=heads[i]; it++) {
					f2 << "\t";
				}
				f2 << "\t^" << endl;
			}
			f2 << "State" << "\t:\t" << currentState << endl;
			f2 << "------------------------------------------------------" << endl;
		}

		void printResult() {
			vector<Tape>::iterator it, it1, it2;
			for(it = tapes[0].begin(); it != tapes[0].end(); it++) {
				it1 = it;
				if((*it).ch != B[0] || it == heads[0]) {
					break;
				}
			}
			for(it = tapes[0].end()-1; it >= tapes[0].begin(); it--) {
				it2 = it;
				if((*it).ch != B[0] || it == heads[0]) {
					break;
				}
			}
			for(it = it1; it <= it2; it++) {
				f3 << (*it).ch;
			}
			f3 << endl;
			// cout << currentState << endl;
		}

		void takeAction(Node node) {
			printCurrent();
			step++;
			currentState = node.nextState;
			for(int i = 0; i < N; i++) {
				if(node.nextTape[i] != '*') {
					heads[i]->ch = node.nextTape[i];
				}
				if(node.direction[i] != '*') {
					if(node.direction[i] == 'l') {
						if(heads[i] == tapes[i].begin()) {
							Tape tape;
							tape.ch = B[0];
							tape.index = tapes[i].begin()->index-1;
							tapes[i].insert(tapes[i].begin(), tape);
							heads[i] = tapes[i].begin();
						} else
							heads[i]--;
					} else {
						if(heads[i]-tapes[i].begin()+1 == tapes[i].size()) {
							Tape tape;
							tape.ch = B[0];
							tape.index = heads[i]->index+1;
							tapes[i].push_back(tape);
							heads[i] = --tapes[i].end();
						} else
							heads[i]++;
					}
				}
			}
		}

		void simulation(string filename) {
			string input;
			f1.open(filename, ios::in);
			/*if(f1 == NULL) {
				cout << filename << "not found" << endl;
				return;
			}*/
			while(getline(f1, input)) {
				//cout << input << endl;
				f2 << "Input: " << input << endl;
				int n;
				for(n = 0; n < input.length(); n++) {
					if(S.count(input[n]) == 0) {
						f2 << "==================== ERR ====================" << endl;
						f2 << "The input \"" << input << "\" is illegal" << endl;
						f2 << "==================== END ====================" <<endl;
						break;
					}
				}
				if(n != input.length()) {
					continue;
				}
				f2 << "==================== RUN ====================" << endl;
				init(input);
				vector<Node>::iterator it;
				int j;
				while(true) {
					vector<Node> candidates;
					for(it = Transition.begin(); it != Transition.end(); it++) {
						// cout << (*it).currentState << endl;
						// cout << currentState << endl;
						// if(currentState[1] == '\r')
						// 	cout << "****" << endl;
						// return;
						if((*it).currentState == currentState) {
							// cout << "***" << endl;
							for(j = 0; j < N; j++) {
								if((*it).currentTape[j] == '*' || tapes[j].size() != 0 && (*it).currentTape[j] == (*(heads[j])).ch) {
									;
								} else {
									break;
								}
							}
							if(j == N) {
								candidates.push_back(*it);
							}
						}
					}
					if(candidates.size() == 0) {
						// print();
						break;
					} else {
						if(candidates.size() == 1) {
							takeAction(candidates[0]);
						} else {
							int minNum = -1;
							int index = 0;
							int counter;
							for(int k = 0; k < candidates.size(); k++) {
								counter = 0;
								for(int m = 0; m < N; m++) {
									if(candidates[k].currentTape[m] == '*') {
										counter++;
									}
									if(candidates[k].nextTape[m] == '*') {
										counter++;
									}
									if(candidates[k].direction[m] == '*') {
										counter++;
									}
								}
								if(minNum == -1 || minNum > counter) {
									minNum = counter;
									index = k;
								}
							}
							takeAction(candidates[index]);
						}
					}
				}
				printCurrent();
				printResult();
			}
		}

		void print() {
			set<string>::iterator it;
			set<char>::iterator it1;
			vector<Node>::iterator it2;
			cout << "Q:" << endl;
			for(it=Q.begin (); it!=Q.end (); it++) {
				cout << *it << endl;
			}
			cout << "S:" << endl;
			for(it1=S.begin (); it1!=S.end (); it1++) {
				cout << *it1 << endl;
			}
			cout << "G:" << endl;
			for(it1=G.begin (); it1!=G.end (); it1++) {
				cout << *it1 << endl;
			}
			cout << "q0:" << q0 << endl;
			cout << "B:" <<B <<endl;
			cout << "F:" <<endl;
			for(it=F.begin (); it!=F.end (); it++) {
				cout << *it << endl;
			}
			cout << "N:" << N << endl;
			cout << "Transition:" << endl;
			for(it2=Transition.begin (); it2!=Transition.end (); it2++) {
				cout << (*it2).currentState << endl;
				cout << (*it2).currentTape << endl;
				cout << (*it2).nextTape << endl;
				cout << (*it2).direction << endl;
				cout << (*it2).nextState << endl;
				cout << endl;
			}
		}
};

int main(int argc, char** argv) {
	string temp = argv[1];
	Turing *turing = new Turing(temp);
	turing->parser(temp+"/test.tm");
	// turing->print();
	turing->simulation(temp+"/input.txt");
	return 0;
}
