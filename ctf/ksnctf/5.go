package main

import (
	"fmt"
	"encoding/base64"
	"strings"
)

func main() {

a := `Vm0wd2QyUXlVWGxWV0d4V1YwZDRWMVl3WkRSV01WbDNXa1JTV0ZKdGVGWlZNakExVmpBeFYySkVU
bGhoTWsweFZtcEdZV015U2tWVQpiR2hvVFZWd1ZWWnRjRWRUTWxKSVZtdFdVZ3BpVlZwWVZtMTRj
MDB4V25GUmJVWlVUV3hLU1ZadGRHdFhRWEJwVW01Q1VGZFhNSGhpCk1WWlhWMjVHVW1KVldtRldh
a0Y0VGxaVmVXUkdaRmRWV0VKd1ZXcEtiMlJzV2tkWGJHUnJDazFXY0ZoV01qVlRZV3hLV0ZWdFJs
ZGgKYTFwTVZURmFZV1JIVWtkYVJscGhUVEJLZDFadGVHRmtNV1JYVjI1U1RsWkdTbkZEYXpGRlVX
cFNWMDFxVmxSWlYzaExWMFpXYzFacwpWbGNLVFRKb1RWWlVSbUZaVjFKSVZXdHNWV0pYYUZkV01G
WkxWbFprV0dWSGRHbE5iRXA2VmpKMGExbFdUa2xSYmtwRVlYcEdlbFl5CmRHOVdNREZ4Vm14U1Yx
SXphR2hWYWtaUFl6RmFjd3BXYkdOTFZGUkJNRTFHV2toa1IwWm9UV3MxTUZWdGRHdFpWa2w1WVVa
T1YwMUcKV2t4V2JGcHJWMGRTU0U5V1NrNVdiSEJKVmpKMFlXSXhVbk5VYTJob1UwVktSVmxZY0Vk
WFJsbDVDbVZIT1ZkTlJFWjRWbTE0VTFZeApTWHBoUjJoV1lXdGFVRmw2Um1GamQzQlhZa2RPVEZa
R1VrdGlNVkpYVjJ4V1UySlZXbUZXYWtaTFUxWmFXR1JIT1doTlZXdzFXVlZhCmExWXdNVWNLVjJ0
NFYySkdjR2hWYWtaaFpFWktkR1JGTlZkTlZYQmFWbTF3U2sxV1ZYbFNiazVVWWtkNFYxbHRkRXRT
Vm14WlkwVmsKV0ZKc1ZqVkRiVlpJVDFab1UwMUdXVEJYVkVKdldWWmtjd3BYYTFwWVlUTlNhRlZy
Vm1GamJIQkdWMnQwYW1RelFtaFZha3ByVkVaawpWMVZyVGxkTlJGWklWMnRvVDFkSFNsWlhiR1JW
VmpOT05GUnJXbXRqYlVaSFZHMW9UbFpZUVhoV1ZtUTBDbUV4V1hkTlZXTkxWakowCk5GWXlTa2Rq
U0VwWFRVZFNXRlV3V2t0ak1WWnlUbFprVGxaWVFtRldiVEYzVXpBeFNGSllhRmhpYkVwVVZqQmtV
MVZHV25SbFIwWlQKVm0xNFdsa3dWbXNLVjBaS2RHUkVUa1JpUjFJd1ZERmFiMVV3TVVkWFZFSllW
a1ZLZGxWNlJscGxVWEJUWW10d2NWVnNhRzlXTVd4WQpaRWhrVmxKc1ZqUldNbmhQWVcxUmVsRnNi
RnBpUjFGM1ZrVmFZUXBrUjFKSFdrWndWMkpJUWxsV2FrbzBWakZWZVZOc1dsaGlWVnBZCldWZDBZ
VlJHVlhoWGJVWllVakZLU1ZReFpHOVViRnBZWkhwR1dGWnNXbkpEYlVsNFYyeGtXR0V4YkV4V1ZF
b3dDazVHV1hsVGEyUnEKVTBWd1dGUlZaRk5YUmxWM1YydDBhazFXV25sVWJGcHJWR3hhV1ZGdFJs
ZGlXRUpNVkZWa1NtVkdWbGxoUjJ4VFlsWktWbGRXVWtkawpNVnBYWWtoT1YySlZXbFFLVm0weE5H
VldXWGxPVjNOTFZtcEtTMUl4WkhGUmExSm9aV3hhWVZZeWRHRmhNVkp6VTJ0YVdHRnNTbGhaCmJG
SkdUVVpXVlZKc2NHdGtNMEpQVm14a2IxWXhiRlZVYlRsWVVtMTRlZ3BaVldNMVlXMUtTVkZyYUZk
TmJrMHhXVmN4VW1Wc1JuVlMKYkZwb1lUSTVNMVpyVm1GWlVYQllVbFJHUmxWdGVFdFViVVY1Wkhw
Q1YyRnJhM2hXVkVwSFl6Rk9jMkZHV21sU01VcG9DbGRYZEdGawpNa1pIVmxoa1dHSklRbk5XYkZK
WFYwWmtjbGR0ZEZkTlJFWktWVmQ0ZDFkR1duTlhiV2hFWWtaR05GWXhhR3RVYkZwWVZHdDRWMkZy
CmIzZERhelZIVjFoc1ZHRXlVbkVLVlRCV2QxZEdVbFphUms1WFVteFdNMVl5ZERCaE1VbDRVMnRr
VldKR2NISldSM2hoVjFaR2RGSnMKWkdsWFJVcE5Wa1pXWVdNeFpFZFViR3hwVW1zMVdWVnFTbTlX
YkZweFVXMTBWZ3BOVjFKWVdXdG9VMkV4VGtoVmJGRkxWbTB3ZUU1RwpaSE5oTTJSWFlsaE9URlpx
UW1GVE1sSklWV3RXVldFeFNuQlZha1pLWkRGYVJWSnRSbWhOVmtwNlZUSjBZVmRIUm5OVGJHaGFD
bUpHClNrZFVWVnBYVmxaS2RHUkdUbXROTUVwYVYxY3hlazFYVGxkV2JrNW9VbnBzV0ZSV1pEUmxa
M0JhVmxkTk1WWnRlRXRrVmtaeVlVWmsKVG1Kc1JqTlhWbU40VlcxV2MxSnVUbWdLVW01Q2IxUlhl
RXRWVmxweVZtMUdhR1F6UWxsVmFrWkxVMVpSZUZkcmRHaFdiSEI2V1RCUwpZVll5Um5KaE0yaFdZ
V3RhV0ZwRldrOWpNV1J6WVVkc1UwMXRhRzlEYkdSWVpFZEdhd3BOYTFwSVZqSTFSMVV5U2taT1dF
WlZWbTFTClZGUlZXbGRrUjFaSVVteGFUbUV6UWt0V1ZscHZZVEZrUjFkdVRsaGlWMmhGV1d0YVIw
NUdXWGhoUjNSVllrWndXVlpIZERSV01rWnkKQ21JelpFUmhlbFpJV1d0YWExWkhSWGhqUm10TFYx
ZDRhMkl4WkVkVmJGcGhVbXMxVjFWdGVHRk5SbXQ2WTBaa1dGSnJiRE5aTUZacgpWbGRLUjJOSVNs
ZFNNMmhvVmpGYVIyTnRVa2NLV2tkc1YxSldiRFpXYkdoM1VXMVdSMVJyWkZSaVIzaHZWV3BDWVZa
R1duRlRiVGxYCllrZFNXVnBGWkRCVWQzQlRZa2QzTUZkWGRHOVZNa1owVm01S1dHSkdSa3hXYlRC
M1pVVTFTQXBXYms1WVlteEtVRlpxVGs5VVJscHgKVVcxR1ZFMXJNVFZWTW5SWFZqSkZlRk51UWxk
aVdGSXpWVEo0WVZKV1NuUlNiV2hPVm10d05sWlVTakJaVm1SSFdrVm9hRkp0YUdGRApiVVY1Q2xW
ck9XRldWbkJ5Vm1wR2EyUkhVa2hqUjNST1RVVndZVll4V2xOU01sRjRXa1prYVZKc1dsWlphMVV4
WWpGV2RHVkhSbXhWCldFSllXV3hTUjFOR2JGaE5WWFJVVWpGSk1sVXllR0VLWVZaa1NHRkliRmhX
YlU0MFZsY3hWMk14U25WVWJXZExWVzAxUTJJeFVsaGwKUlhSV1ZteHdlVlp0TVVkaFIxRjZVV3hz
Vm1GcldreFZNVnBYWkVkV1NHUkdWbWxTV0VKSlZtcEtNQXBqTVZsNVVtNUthV1ZyU21GWgpWM1Iz
VTBac05sSnJPV3BOYTFwSVZqSXhjMVV3TVZaalJtaEVZa1p3TUZrd1ZUVldVWEJPVWtaYVNWWnNZ
ekZUTVdSSVUydHNVbUpyCk5WaFphMXBMQ2xkR1duRlNiRXBzVW0xU01GcEZXbXRVYkVwR1YydDBW
MVp0VVhkYVJFWmFaVlpPY21GR1dsZFNWWEJHVjFkNFYxWXcKTlVkWFdHaG9Vak5TVmxsclduZFhW
bHBJWkVSU1YwMXJXbmtLUTIxSmVscEZVbWhsYkZwSlZtcEdiMkV4VW5OYVJXUllZbFJvVEZacwpa
SGRUTWtsNFdrVmtWbUpHY0ZsWmEyUlRWVVpXZEdWSVpHeGlSbXcxV2tWa01HRkZNVlppUkZKV1RX
NVNjZ3BXYkdSTFVqSk9TVk5zCmNGZGlTRUpSVmxjeE5GUXlUblJWYTJOTFYydGtjMWRHU2xaalJU
VlhZVEZ3V0ZsVVJrOWtSbHB5V2taa2FWSXphSFpXVjNCRFdWWmEKVjFadVRtaFNWVFZYQ2xWdGVI
ZFdiRlpZVFZSQ1ZXUXpRbFJaYTJRelRVWmtXR1JIT1ZSTlZtdzFWV3hvZDFadFNrZFNhM2hYWWxS
QwpNMXBWVlRGVFFYQlhZa2RTV1ZsdGVFdFZSbHB6VlcwNVZWSnNjSGtLVmxkMGExWkZNWEpOVkZK
WVlUSm9TRlpYTVVabFJrNTFVV3hrCmFWSnJjRmxXVkVaaFdWZE9jMk5GVmxaaVYyaFBWbTEwZDA1
c1duRlRhbEpwVFZaYVNGWkhkRzlpUmtwMFlVZEdSQXBpVlhCSVEyeE8KY2xwR1ZsZFdia0paVm0x
NFlWTXlUWGxVYTJoc1VteHdXVlZzVm5kV01WbDRXa1JDV2xadGVGaFdNblJyWVZaS2MxZHNXbHBp
UmtwNgpWakZhVjJSSFZrWmtSbWhTQ2xkRlNsbFdSbVIzVmpKT2MxZHVTbGhoTTFKeVZXcEdTazFz
VlhsbFIwVkxXVlphYTFJeFRuVmlSbWhYCllsVTBNRlpzWTNoV01rMTRVMjVXVm1KWFpFeFdWekUw
WkRKSmVHSkdWbFFLVmtaYVQxUldXbmRsVmxwMFRWVmtXR0pHV2xwVlYzaHoKVm0xS1IxTnJhRmRp
V0doWVZqQlZlRlpXUm5OV2JXeFRZbXRHTkZac1dtdE9RWEJxVFZac05WVnROVXRoVlRCNVZXMUdW
d3BoTVZwbwpXVlZhZDFKc1pISmtSbWhYVFVoQ1NWWnFTWGhqTWtaR1RWWnNVbUpIYUVWWmExcDNU
VVpTVm1GSE9WZGFNMEpQVm0wMVExTldXbkZTCmJUbHBUVmRTU1ZVeWVHRlhSMHBIQ2xkc1pGcFdN
MUpvUTJ4U1IxWllhRmhpUjFKeVZXcEdZVk5XVm5SbFIwWlZZbFZXTmxWWGREQlcKTVZwMFZXcE9X
RlpzY0dGYVZscExaRlpPZEdGRk5VNWlWMmhIVmpGa01GWnRWa1lLVGxWa1dGZEhlSE5WYWs1VFYx
WldjVkZzWkU5UwpiWGg1Vm0xd1UxWXdNVmRqUldOTFVUSXhTbVZzY0VaVmJXaHNZa1p3U2xadGNF
ZGlNazE0Vmxob1lWSlhhRzlWTUZaWFZFWmFjd3BhClNHUlVUV3RzTkZZeGFHOWhWa3AwWVVoS1Zt
RnJTbWhaTVZwelkyeHdSVlJyTldsU2JHOTNWa2Q0YTAxR1dYaFRia3BwVWtaS1YxUlgKTlZOaloz
QlhZa2RTVEZWcVNrOVRWazV6Q2xwRk5WTmlhMHBPVm0wd2QyVkdVWGhUYmxKV1lUSk9URll5ZEd0
ak1WbDRVMnhrYVZKRwpjRmhaYTFwTFZFWndXRTFXWkZOTlYxSmFXVlZhYjJGV1NYcGhTR1JYVm5w
Rk1GVjZTa29LWlVaV2MyRkhlRk5YUmtwWlEyeHNjbHBHClRsaFdia0pIVjJ0U1EyRkdWbGxSYXps
WFlsUkZlbFJWV210WFIxSklUMVphVG1FeFdUQldhMlF3WWpGYWRGTnJaRk5oTTJoWVdXeFMKUXdw
Tk1YQldWbFJHVkZGWVFsaFpiWE14VjFac2RHVkZkRlpTYkhCNFZrZHpOVlpXU25OalJFRkxWMnRX
YTFJeFpITlhXR1JPVmtaSwpWMVJYY0ZkVFJscDBUVlZhYkZKck5URlZWM2hoQ21GV1pFaGFNM0JY
VWpOb2FGZFdXa3RXTVU1MVZXeE9hVll5YUZCV2JURXdaREExCmMxZHVSbFJoYkVwd1ZGWmFZVk5H
V2toa1J6bHBVbXR3TUZsVlpFZFNRWEJwVmxoQ1NWRXllRThLWTJ4d1IxWnNaRmRpYTBwMlZtMHgK
TkZsV1RYbFVXR3hWWVRKb2MxVnRlSGRYVmxaelZtNWtWMkpHYkRSWFZFNXZWR3hKZUZKcVZsZFNN
Mmh5Vm1wS1MyTnJOVmhQVmxwcApZbXRLTmdwV01WcGhXVmRTUms1V1dsVmlSMmhYUTJ4a1JsTnRP
VmRXTTJoeVZsUkdUMUl5U2tkaFJUVlhWMFpLVmxadE1UQlpWMVpYCldraEtXR0pVYUV4WFZsWlda
VVpaZVZScmJHbFNiVkp3Q2xWdGRIZFVWbHB6V1ROb1YwMXJNVFJWTWpWWFZsZEtXR1JGZUZkV2Vr
RjQKVlZSS1NtVkdWbk5oUjNkTFZXeG9VMVl4V25SbFNHUnNWbXh3TUZSV1ZtdGhSa2w0VW1wYVZs
WXphSG9LVm0weFIyTnNaSFJoUmxwTwpVbTVDYUZkc1dsWmxSbHBYVW01T1YySlhlRmhXTUZaTFUx
WmFkR05GWkZaa00wSlRWRlphYzA1V1ZuUk9WWFJvVmxSQ05WWlhlRzlYClozQlhUVEZLYndwV2JY
QkhaREZaZUZwSVNsQldNMEp3Vm14YWQxTldXbkZUV0docVRWWldOVlV5TlV0V1IwcElZVVZXV21F
eGNETlUKVlZweVpERmFWVlpzWkdGTk1FcFFWbGQwVjFOck1VZGFSbFpTQ21KVlduQlVWM1IzVTBa
VmVVNVdUbGRpVlhCSlEyMVdSMXBHY0ZkTgpNVXB2VVRJeFIxSXhXbGxhUm1ocFYwWktlRmRYZEd0
Vk1sWnpXa2hLWVZKNmJGaFVWM1JYVG14V1dFMVZaRmNLVFZad01GWkhjRk5XCmJVWnlWMjFHWVZa
c2NFeFdNV1JMVWpGa2MyRkdUazVXV0VKSVZtcEdZV0l5VVhoWFdHZExWa2QwYTFZeFpFaGxTRXBX
WVdzMVZGbHEKUm5OamJGcDFXa1pTVXdwaVdHZzFWbTB4ZDFVeFdYZE5WbHBxVTBjNVRGVlVTalJo
TWsxNFZtNUtWbUpYZUZoV2ExWldaREZhYzFWcgpkRTVTTUZZMVZXMDFUMVpIUlhsVmJrWldZa1pL
ZGxaRldtRmpkM0JoQ2xKRlNtOVVWVkpYVTBaVmVXVkhkRnBXYXpWSVZqSTFRMVpXCldrWmpSbEpY
Vm14d2FGbDZSbUZXVmtwMFpFWmthVkp1UWtwV2JYaGhZakpGZUZkcmFGWlhSM2hSVld0a05GSlda
SFVLWWpOa1VGVlkKUWtWWGJtOTNUMVZPYmxCVU1Fc0sK`
	for i := 0; i < 30; i++ {
		d, _ := base64.StdEncoding.DecodeString(a)
		a = string(d)
		if strings.HasPrefix(a, "begin") {
			break
		}
	}
	fmt.Println(a)
}
