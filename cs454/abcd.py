from itertools import permutations


def main():
    perms = [''.join(p) for p in permutations('abcd')]
    print(len(perms))

    aa = [''.join(p) for p in permutations('abcdaa')]  # 2 As
    aa_set = set(aa)

    ab = [''.join(p) for p in permutations('abcdab')]  # 1 A 1 B
    ab_set = set(ab)

    ac = [''.join(p) for p in permutations('abcdac')]  # 1 A 1 C
    ac_set = set(ac)

    ad = [''.join(p) for p in permutations('abcdad')]  # 1 A 1 D
    ad_set = set(ad)

    bb = [''.join(p) for p in permutations('abcdbb')]  # 2 Bs
    bb_set = set(bb)

    bc = [''.join(p) for p in permutations('abcdbc')]  # 1 B 1 C
    bc_set = set(bc)

    bd = [''.join(p) for p in permutations('abcdbd')]  # 1 B 1 D
    bd_set = set(bd)

    cc = [''.join(p) for p in permutations('abcdcc')]  # 2 Cs
    cc_set = set(cc)

    cd = [''.join(p) for p in permutations('abcdcd')]  # 1 C 1 D
    cd_set = set(cd)

    dd = [''.join(p) for p in permutations('abcddd')]  # 2 Ds
    dd_set = set(dd)

    combine = aa_set|ab_set|ac_set|ad_set|bb_set|bc_set|bd_set|cc_set|cd_set|dd_set
    check = 0
    print(sorted(combine))


if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
