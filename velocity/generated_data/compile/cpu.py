from dace import SDFG


def main():
    g = SDFG.from_file('velocity.sdfg')
    g.build_folder = 'codegen/cpu'
    g.compile()


if __name__ == '__main__':
    main()
