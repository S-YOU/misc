# �n�C�u���b�h���J���Í�

## [HPKE](https://www.ietf.org/archive/id/draft-irtf-cfrg-hpke-09.html)

��M�҂̌��J���ɑ΂��āA�C�ӃT�C�Y�̕����̔F�ؕt�����J���Í������s���B

- KEM ; ���ʌ��̃J�v�Z����
- HKDF ; HMAC�x�[�X�̌����o�֐�
- AEAD ; �F�ؕt���Í�
- ECDH ; �ȉ~�Ȑ��ɂ��DH�����L

�𗘗p����B

�]���̃n�C�u���b�h�Í��́A���ʌ������J���ňÍ�������d�g�݂̒莮���B
HPKE�͋��ʌ��𐶐����A��������J���ňÍ�������d�g�ݑS�̂�莮������B

�]���̕����͑��݉^�p�ɓ����A�Â��Í��v���~�e�B�u�Ɋ�Â��Ă�����A�ؖ����Ȃ�������A�e�X�g�x�N�g�����Ȃ��ł��B
IND-CCA2���S�Ȃ��̂�ڎw���B

## �L��
- S ; �Í����̑��M��
- R ; �Í����̎�M��
- E ; ��񂾂��̃����_���Ȗ���
- (skX, pkX) ; S��{S, R, E}�ɑ΂���KEM
  - skX ; �閧��
  - pkX ; ���J��
- pk(skX) ; �閧��skX�ɑΉ�������J��

### KEM
- (skX, pkX) �� GenerateKeyPair() ; �����_���Ȍ������A���S���Y��
- (skX, pkX) �� DeriveKeyPair(ikm) ; ikm����͂Ƃ��錈��I�������A���S���Y��
- enc �� Encap(pkR) ; �ꎞ�I�ȋ��ʌ��Í��̔閧���𐶐�����pkR�ɑΉ�����閧���ŕ����\�Ȍ��J���ŃJ�v�Z�������郉���_���A���S���Y��
- Decap(enc, skR) ; enc��skR�ŕ������Ĉꎞ�I�ȋ��ʌ��Í��̔閧���𕜍�����A���S���Y��
- enc �� AuthEncap(pkR, skS) ; skS�ɂ��F�؋@�\�tEncap(pkR)
- AuthDecap(enc, skR, pkS) ; pkS�ɂ�茟�؉\��Decap(enc, skR)

### KDF
- prk �� Extract(salt, ikm) ; ikm��salt(option)����[�������������o���A���S���Y��
- Expand(prk, info, L) ; info��p����prk���������΂���L�o�C�g�̏o�͂𓾂�

## AEAD
- ct �� Seal(key, nonce, aad, pt) ; ���ʌ�key�ƃi���Xnonce�ƕt���f�[�^aad, ����pt���Í���
- pt or bot �� Open(key, nonce, aad, ct) ; ct�𕜍����Đ��������pt. �����łȂ����bot

## DH�x�[�X��KEM
- DH(skX, pkY) ; ��ΘbDH�����L

### �Í����̊T�v

```
def Encap(pkR): ; ��M�҂̌��J��pkR
  skE, pkE = GenerateKeyPair() ; �ꎞ�I�Ȕ閧��skE�ƌ��J��pkE�����
  dh = DH(skE, pkR)            ; pkR��skE��DH�����L����dh�����
  key = ExtractAndExpand(dh, pkE, pkR) ; dh��pkE��pkR���狤�L�閧��key�����
  return key, pkE
```

def Decap(pkE, skR): ; ���M�҂̌��J��pkE�Ǝ�M�҂̔閧��skR
  dh = DH(skR, pkE)  ; DH�����L

  key = ExtractAndExpand(dh, pkE, pk(skR))
  return key

def AuthEncap(pkR, skS):
  skE, pkE = GenerateKeyPair()
  dh = concat(DH(skE, pkR), DH(skS, pkR))
  enc = SerializePublicKey(pkE)

  pkRm = SerializePublicKey(pkR)
  pkSm = SerializePublicKey(pk(skS))
  kem_context = concat(enc, pkRm, pkSm)

  shared_secret = ExtractAndExpand(dh, kem_context)
  return shared_secret, enc

def AuthDecap(enc, skR, pkS):
  pkE = DeserializePublicKey(enc)
  dh = concat(DH(skR, pkE), DH(skR, pkS))

  pkRm = SerializePublicKey(pk(skR))
  pkSm = SerializePublicKey(pkS)
  kem_context = concat(enc, pkRm, pkSm)

  shared_secret = ExtractAndExpand(dh, kem_context)
  return shared_secret

```
