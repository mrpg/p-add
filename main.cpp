/*
 * main.cpp
 *
 * 2014 Max R. P. Grossmann <p-add@max.pm>
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details.
 *
 */

#include <iostream>
#include <gmpxx.h>
#include <vector>
#include <thread>

using namespace std;

int thrn;
vector<thread> t;
vector<pair<mpz_class,mpz_class>> fractions;
vector<pair<mpz_class,mpz_class>> res;

inline void add(const mpz_class& a1, const mpz_class& a2,
                const mpz_class& b1, const mpz_class& b2,
                mpz_class& r1, mpz_class& r2) {
	r1 = a1*b2+a2*b1; // a/b+c/d == (a*d+b*c)/(b*d)
	r2 = a2*b2;
}

void add_thr(int resid) {
	pair<mpz_class,mpz_class> *r = &res[resid], *cur;
	bool init = true;
	int cid = resid, max = fractions.size();

	for (; cid < max; cid += thrn) {
		cur = &fractions[cid];

		if (init) {
			r->first = cur->first;
			r->second = cur->second;

			init = false;
		}
		else {
			add(r->first,r->second,cur->first,cur->second,r->first,r->second);
		}
	}
}

int main(int argc, char** argv) {
	if (argc == 2) {
		thrn = atoi(argv[1]);
	}
	else {
		thrn = thread::hardware_concurrency();
		if (thrn == 0) thrn = 1;
		cerr << "note: number of threads = " << thrn << endl;
	}

	t.resize(thrn);
	res.resize(thrn,pair<mpz_class,mpz_class>(0,1));

	pair<mpz_class,mpz_class> cur;

	while (cin >> cur.first >> cur.second) {
		fractions.push_back(cur);
	}

	for (int i = 0; i < thrn; i++) {
		t[i] = thread(add_thr,i);
	}

	for (int i = 0; i < thrn; i++) {
		t[i].join();
		cout << res[i].first << endl;
		cout << res[i].second << endl;
	}
}
