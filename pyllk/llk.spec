# -*- mode: python -*-
a = Analysis(['llk.py'],
             pathex=['/home/geeksword/python/PyLLK'],
             hiddenimports=[],
             hookspath=None,
             runtime_hooks=None)
pyz = PYZ(a.pure)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          name='llk',
          debug=False,
          strip=None,
          upx=True,
          console=True )
