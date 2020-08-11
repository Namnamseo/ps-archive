state = 0
cur = [0, 0, 0]

s = []

def commit():
	global cur, s
	if cur != [0, 0, 0]:
		s.append(cur)
		cur = [0, 0, 0]

def jaum(x):
	return x in 'qwertasdfgzxcvREQTW'

def jaja(x, y):
	return (x+y) in {
	'rt', 'sw', 'sg', 'fr', 'fa', 'fq', 'ft', 'fx',
	'fv', 'fg', 'qt'
	}

def momo(x, y):
	return (x+y) in {
	'hk', 'ho', 'hl', 'nj', 'np', 'nl', 'ml'
	}

ans = 0
def add_char(x):
	global state, cur, ans
	while True:
		if state == 0:
			if not jaum(x):
				break
			cur = [x, 0, 0]
			state = 1
			break
		## 중성 대기중
		if state == 1:
			if jaum(x):
				commit()
				state = 0
				continue
			cur[1] = x
			state = 2
			break
		## 종성/겹모음 대기중
		if state == 2:
			# 고 ->
			if jaum(x) and x not in 'EQW':
				# 곡
				cur[2] = [x]
				state = 3
				break
			if jaum(x):
				commit()
				state = 0
				continue
			if momo(cur[1], x):
				# 과
				cur[1] += x
				break
			# 고ㅗ
			commit()
			state = 0
			break
		## 종성 입력받은 상태
		if state == 3:
			if jaum(x):
				if len(cur[2]) == 1 and jaja(cur[2][0], x):
					cur[2].append(x)
					break
			else:
				t = cur[2][-1]
				cur[2] = cur[2][:-1]
				if not cur[2]:
					cur[2] = 0
				commit()
				cur = [t, x, 0]
				ans += 1
				state = 2
				break
			commit()
			state = 0
			continue

import sys
S = sys.stdin.readline()[:-1]

def init():
	global state, cur, s
	s = []
	state = 0
	cur = [0, 0, 0]

def Print():
	ja = {
	'r': 'ㄱ',
	's': 'ㄴ',
	'e': 'ㄷ',
	'f': 'ㄹ',
	'a': 'ㅁ',
	'q': 'ㅂ',
	't': 'ㅅ',
	'd': 'ㅇ',
	'w': 'ㅈ',
	'c': 'ㅊ',
	'z': 'ㅋ',
	'x': 'ㅌ',
	'v': 'ㅍ',
	'g': 'ㅎ',
	'R': 'ㄲ',
	'T': 'ㅆ',
	'E': 'ㄸ',
	'W': 'ㅉ',
	'Q': 'ㅃ'
	}
	mo = {
		'k': 'ㅏ',
		'i': 'ㅑ',
		'j': 'ㅓ',
		'u': 'ㅕ',
		'h': 'ㅗ',
		'y': 'ㅛ',
		'n': 'ㅜ',
		'b': 'ㅠ',
		'm': 'ㅡ',
		'l': 'ㅣ',
		'o': 'ㅐ',
		'O': 'ㅒ',
		'p': 'ㅔ',
		'P': 'ㅖ'
	}

	res = ''
	for a, b, c in (s + [cur]):
		def conv(x):
			if x == 0:
				return ''
			if len(x) > 1:
				return list(map(conv, x))
			if type(x) == list:
				x = x[0]
			if x in ja: return ja[x]
			return mo[x]

		a = conv(a)
		b = conv(b)
		c = conv(c)
		res += str((a, b, c))

	print(res)

for x in S:
	if x == ' ':
		commit()
		state = 0
		continue
	add_char(x)
	Print()

print(ans)
