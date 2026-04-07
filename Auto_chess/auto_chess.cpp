#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Piece {
	int id;   //编号
	int side; //1:攻 0:守
	int col, row;
	int hp, atk, def, spd, rng;
	bool alive;
};

const int H = 6;
const int W = 6;

// board[row][col] = piece id, -1空
int board_[H][W];
vector<Piece> pieces;

// 偶数行(row % 2 == 0)六个方向
int dc_even[6] = { 0, 1, 0, -1, -1, -1 };
int dr_even[6] = { -1, 0, 1, 1, 0, -1 };

// 奇数行
int dc_odd[6] = { 1, 1, 1, 0, -1, 0 };
int dr_odd[6] = { -1, 0, 1, 1, 0, -1 };

//是否在棋盘内
bool in_board(int c, int r) {
	return (c >= 0 && c < W && r >= 0 && r < H);
}

//offset -> cube
void offset_to_cube(int col, int row, int& x, int& y, int& z) {
	x = col - (row - (row & 1)) / 2;
	z = row;
	y = -x - z;
}

//六边形距离
int hex_dist(int c1, int r1, int c2, int r2) {
	int x1, y1, z1, x2, y2, z2;
	offset_to_cube(c1, r1, x1, y1, z1);
	offset_to_cube(c2, r2, x2, y2, z2);
	return ((abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)) / 2);
}

//获取某个格子的第dir个邻居
pair<int, int> get_neighbor(int c, int r, int dir) {
	if (r % 2 == 0) {
		return { c + dc_even[dir], r + dr_even[dir] };
	}
	else {
		return { c + dc_odd[dir], r + dr_odd[dir] };
	}
}

//统计双方存活数量
pair<int, int> count_alive() {
	int atk_alive = 0, def_alive = 0;
	for (auto& p : pieces) {
		if (!p.alive) continue;
		if (p.side == 1) atk_alive++;
		else def_alive++;
	}
	return { atk_alive, def_alive };
}

//为某个棋子选最近目标
int choose_target(int id) {
	Piece& me = pieces[id];
	int best_id = -1;
	int best_dist = INT_MAX;

	for (auto& enemy : pieces) {
		if (!enemy.alive) continue;
		if (enemy.side == me.side) continue;

		int d = hex_dist(me.col, me.row, enemy.col, enemy.row);
		if (d < best_dist || (d == best_dist && enemy.id < best_id)) {
			best_dist = d;
			best_id = enemy.id;
		}
	}
	return best_id;
}

//攻击
void attack_target(int attacker_id, int target_id) {
	Piece& attacker = pieces[attacker_id];
	Piece& target = pieces[target_id];

	//目标可能被前面的打死
	if (!attacker.alive || !target.alive) return;

	int damage = attacker.atk * attacker.atk / (attacker.atk + target.def);
	target.hp -= damage;

	if (target.hp <= 0) {
		target.alive = false;
		board_[target.row][target.col] = -1;
	}
}

//移动
void move_towards(int mover_id, int target_id) {
	Piece& me = pieces[mover_id];
	Piece& target = pieces[target_id];

	if (!me.alive || !target.alive) return;

	int best_dir = -1;
	int best_c = -1, best_r = -1;
	int best_dist = INT_MAX;

	for (int dir = 0; dir < 6; dir++) {
	    auto [nc, nr] = get_neighbor(me.col, me.row, dir);

		if (!in_board(nc, nr)) continue;
		if (board_[nc][nr] != -1) continue;

		int d = hex_dist(nc, nr, target.col, target.row);

		if (d < best_dist) {
			best_dist = d;
			best_dir = dir;
			best_c = nc;
			best_r = nr;
		}
	}

	if (best_dir == -1) return;

	board_[me.row][me.col] = -1;
	me.col = best_c;
	me.row = best_r;
	board_[me.row][me.col] = me.id;
}

int main() {
	int N, M;
	cin >> N >> M;

	pieces.clear();
	pieces.reserve(N + M);

	for (int r = 0; r < H; ++r) {
		for (int c = 0; c < W; ++c) {
			board_[r][c] = -1;
		}
	}

	//前N个进攻方，后M个防守方
	for (int i = 0; i < N + M; ++i) {
		Piece p;
		p.id = i;
		p.side = (i < N ? 1 : 0);
		cin >> p.col >> p.row >> p.hp >> p.atk >> p.def >> p.spd >> p.rng;
		p.alive = true;

		pieces.push_back(p);
		board_[p.row][p.col] = p.id;
	}

	//最多模拟100帧
	for (int frame = 1; frame <= 100; frame++) {
		//本帧开始时生成行动顺序
		vector<int> order;
		for (auto& p : pieces) {
			if (p.alive) order.push_back(p.id);
		}

		sort(order.begin(), order.end(), [&](int a, int b) {
			if (pieces[a].spd != pieces[b].spd) return pieces[a].spd > pieces[b].spd;
			return pieces[a].id < pieces[b].id;
			});

		//按顺序行动
		for (int id : order) {
			if (!pieces[id].alive) continue;

			int target_id = choose_target(id);
			if (target_id == -1) continue;

			int d = hex_dist(pieces[id].col, pieces[id].row,
				pieces[target_id].col, pieces[target_id].row);
			if (d <= pieces[id].rng) {
				attack_target(id, target_id);
			}
			else {
				move_towards(id, target_id);
			}
		}

		//每帧结束检查
		auto [atk_alive, def_alive] = count_alive();

		if (atk_alive > 0 && def_alive == 0) {
			cout << 1 << " " << frame << endl;
			return 0;
		}
		if (atk_alive == 0 && def_alive > 0) {
			cout << 0 << " " << frame << endl;
			return 0;
		}
		if (atk_alive == 0 && def_alive == 0) {
			cout << 2 << " " << frame << endl;
			return 0;
		}
	}

	//100帧未结束
	cout << 2 << " " << 100 << endl;
	return 0;
}