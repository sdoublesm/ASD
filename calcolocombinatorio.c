#include <stdio.h>
#include <stdio.h>

// Powerset (Insieme della parti) -----------------------------------------
int powerset(int n, int pos, int *val, int *pos, int start, int cnt){
	int i;
	if(start>=n){
		for(i; i<pos; i++){
			printf("%d", sol[i]);
		}
		return cnt+1;
	}
	for(i=start; i<n; i++){
		sol[pos] = val[i];
		cnt = powerset(n, pos+1, val, pos, i+1, cnt);
	}
	cnt = powerset(n, pos, val, pos, n, cnt);
	return cnt;
}

// Disposizioni con ripetizione -----------------------------------------
int disp_rip(int n, int pos, int *val, int *pos, int k, int cnt){
	int i;
	if(pos>=k){
		for(i=0; i<pos; i++){
			printf("%d", sol[i]);
		}
		return cnt+1;
	}
	for(i=0; i<n; i++){
		sol[pos] = val[i];
		cnt = disp_rip(n, pos+1, val, pos, k, cnt);
	}
	return cnt;
}

// Permutazioni semplici -----------------------------------------
// Utile per generare ANAGRAMMI con lettere NON ripetute
int permut_s(int n, int pos, int *val, int *sol, int *mark, int cnt){
	int i;
	if(pos>=n){
		for(i=0; i<pos; i++){
			printf("%s", sol[i]);
		}
		return cnt+1;
	}
	for(i=0; i<n; i++){
		if(mark[i]==0){
			mark[i]=1;
			sol[pos] = val[i];
			cnt = permut_s(n, pos+1, val, pos, mark, cnt);
			mark[i]=0;
		}
		return cnt;
	}
}

// Combinazioni con ripetizione ------------------------------------
int comb_r(int n, int pos, int *val, int *sol, int start, int k, int cnt){
	int i;
	if(pos>=k){
		for(i=0; i<k; i++){
			printf("%d", sol[i]);
		}
		return cnt+1;
	}
	for(i=start, i<n; i++){
		sol[pos] = val[i];
		cnt = comb_r(n, pos+1, val, sol, start, cnt, k, cnt);
	start++;
	}
	return  cnt;
}

// Partitioni di un insieme ------------------------------------
void ER(int n, int m, int pos, int *val, int *sol, int k){
	int i, j;
	if(pos>=n){
		if(m==k){
			for(i=0; i<m; i++){
				for(j=0; j<n; j++){
					if(sol[j] == i){
						pritnf("%d ", val[j]);
					}
				}
			}
		}
		return;
	}
	for(i=0; i<m; i++){
		sol[pos]=i;
		ER(n, m, pos+1, val, sol, k);
	}
	sol[pos] = m;
	ER(n, m+1, pos+1, val, sol, m);
}