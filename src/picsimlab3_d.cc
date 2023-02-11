CPWindow3::CPWindow3(void) {
    // lxrad automatic generated block start, don't edit below!
    SetFOwner(this);
    SetClass(lxT("CPWindow"));
    SetName(lxT("window3"));
    SetTag(0);
    SetX(309);
    SetY(188);
    SetWidth(552);
    SetHeight(391);
    SetHint(lxT(""));
    SetEnable(1);
    SetVisible(0);
    SetPopupMenu(NULL);
    SetTitle(lxT("PICSimLab - Configuration"));
    SetOverrideRedirect(0);
    EvOnCreate = EVONCREATE & CPWindow3::_EvOnCreate;
    EvOnShow = EVONSHOW & CPWindow3::_EvOnShow;
    // label1
    label1.SetFOwner(this);
    label1.SetClass(lxT("CLabel"));
    label1.SetName(lxT("label1"));
    label1.SetTag(0);
    label1.SetX(51);
    label1.SetY(44);
    label1.SetWidth(87);
    label1.SetHeight(20);
    label1.SetHint(lxT(""));
    label1.SetEnable(1);
    label1.SetVisible(1);
    label1.SetPopupMenu(NULL);
    label1.SetText(lxT("Serial Port:"));
    label1.SetAlign(1);
    CreateChild(&label1);
    // label2
    label2.SetFOwner(this);
    label2.SetClass(lxT("CLabel"));
    label2.SetName(lxT("label2"));
    label2.SetTag(0);
    label2.SetX(56);
    label2.SetY(240);
    label2.SetWidth(82);
    label2.SetHeight(20);
    label2.SetHint(lxT(""));
    label2.SetEnable(1);
    label2.SetVisible(1);
    label2.SetPopupMenu(NULL);
    label2.SetText(lxT("Prog. Port:"));
    label2.SetAlign(1);
    CreateChild(&label2);
    // button1
    button1.SetFOwner(this);
    button1.SetClass(lxT("CButton"));
    button1.SetName(lxT("button1"));
    button1.SetTag(0);
    button1.SetX(159);
    button1.SetY(299);
    button1.SetWidth(93);
    button1.SetHeight(28);
    button1.SetHint(lxT(""));
    button1.SetEnable(1);
    button1.SetVisible(1);
    button1.SetPopupMenu(NULL);
    button1.EvMouseButtonClick = EVMOUSEBUTTONCLICK & CPWindow3::button1_EvMouseButtonClick;
    button1.SetText(lxT("Save"));
    CreateChild(&button1);
    // combo1
    combo1.SetFOwner(this);
    combo1.SetClass(lxT("CCombo"));
    combo1.SetName(lxT("combo1"));
    combo1.SetTag(0);
    combo1.SetX(145);
    combo1.SetY(36);
    combo1.SetWidth(200);
    combo1.SetHeight(32);
    combo1.SetHint(lxT(""));
    combo1.SetEnable(1);
    combo1.SetVisible(1);
    combo1.SetPopupMenu(NULL);
    combo1.SetItems(lxT(""));
    combo1.SetText(lxT(""));
    combo1.SetReadOnly(0);
    CreateChild(&combo1);
    // combo2
    combo2.SetFOwner(this);
    combo2.SetClass(lxT("CCombo"));
    combo2.SetName(lxT("combo2"));
    combo2.SetTag(0);
    combo2.SetX(145);
    combo2.SetY(237);
    combo2.SetWidth(200);
    combo2.SetHeight(32);
    combo2.SetHint(lxT(""));
    combo2.SetEnable(0);
    combo2.SetVisible(1);
    combo2.SetPopupMenu(NULL);
    combo2.SetItems(lxT(""));
    combo2.SetText(lxT(""));
    combo2.SetReadOnly(0);
    CreateChild(&combo2);
    // label3
    label3.SetFOwner(this);
    label3.SetClass(lxT("CLabel"));
    label3.SetName(lxT("label3"));
    label3.SetTag(0);
    label3.SetX(61);
    label3.SetY(123);
    label3.SetWidth(77);
    label3.SetHeight(20);
    label3.SetHint(lxT(""));
    label3.SetEnable(1);
    label3.SetVisible(1);
    label3.SetPopupMenu(NULL);
    label3.SetText(lxT("AVR DBG:"));
    label3.SetAlign(1);
    CreateChild(&label3);
    // combo3
    combo3.SetFOwner(this);
    combo3.SetClass(lxT("CCombo"));
    combo3.SetName(lxT("combo3"));
    combo3.SetTag(0);
    combo3.SetX(145);
    combo3.SetY(117);
    combo3.SetWidth(200);
    combo3.SetHeight(32);
    combo3.SetHint(lxT(""));
    combo3.SetEnable(1);
    combo3.SetVisible(1);
    combo3.SetPopupMenu(NULL);
    combo3.SetItems(lxT("GDB,MDB,"));
    combo3.SetText(lxT("GDB"));
    combo3.SetReadOnly(0);
    CreateChild(&combo3);
    // label4
    label4.SetFOwner(this);
    label4.SetClass(lxT("CLabel"));
    label4.SetName(lxT("label4"));
    label4.SetTag(0);
    label4.SetX(31);
    label4.SetY(83);
    label4.SetWidth(109);
    label4.SetHeight(20);
    label4.SetHint(lxT(""));
    label4.SetEnable(1);
    label4.SetVisible(1);
    label4.SetPopupMenu(NULL);
    label4.SetText(lxT("DBG TCP Port:"));
    label4.SetAlign(1);
    CreateChild(&label4);
    // spin1
    spin1.SetFOwner(this);
    spin1.SetClass(lxT("CSpin"));
    spin1.SetName(lxT("spin1"));
    spin1.SetTag(0);
    spin1.SetX(145);
    spin1.SetY(77);
    spin1.SetWidth(200);
    spin1.SetHeight(32);
    spin1.SetHint(lxT(""));
    spin1.SetEnable(1);
    spin1.SetVisible(1);
    spin1.SetPopupMenu(NULL);
    spin1.SetValue(1234);
    spin1.SetMin(0);
    spin1.SetMax(65535);
    CreateChild(&spin1);
    // spin2
    spin2.SetFOwner(this);
    spin2.SetClass(lxT("CSpin"));
    spin2.SetName(lxT("spin2"));
    spin2.SetTag(0);
    spin2.SetX(145);
    spin2.SetY(157);
    spin2.SetWidth(200);
    spin2.SetHeight(32);
    spin2.SetHint(lxT(""));
    spin2.SetEnable(1);
    spin2.SetVisible(1);
    spin2.SetPopupMenu(NULL);
    spin2.SetValue(5000);
    spin2.SetMin(0);
    spin2.SetMax(65535);
    CreateChild(&spin2);
    // label5
    label5.SetFOwner(this);
    label5.SetClass(lxT("CLabel"));
    label5.SetName(lxT("label5"));
    label5.SetTag(0);
    label5.SetX(25);
    label5.SetY(164);
    label5.SetWidth(116);
    label5.SetHeight(20);
    label5.SetHint(lxT(""));
    label5.SetEnable(1);
    label5.SetVisible(1);
    label5.SetPopupMenu(NULL);
    label5.SetText(lxT("Remote C. Port:"));
    label5.SetAlign(1);
    CreateChild(&label5);
    // button2
    button2.SetFOwner(this);
    button2.SetClass(lxT("CButton"));
    button2.SetName(lxT("button2"));
    button2.SetTag(0);
    button2.SetX(281);
    button2.SetY(299);
    button2.SetWidth(93);
    button2.SetHeight(28);
    button2.SetHint(lxT(""));
    button2.SetEnable(1);
    button2.SetVisible(1);
    button2.SetPopupMenu(NULL);
    button2.EvMouseButtonClick = EVMOUSEBUTTONCLICK & CPWindow3::button2_EvMouseButtonClick;
    button2.SetText(lxT("Cancel"));
    CreateChild(&button2);
    // button3
    button3.SetFOwner(this);
    button3.SetClass(lxT("CButton"));
    button3.SetName(lxT("button3"));
    button3.SetTag(0);
    button3.SetX(145);
    button3.SetY(198);
    button3.SetWidth(200);
    button3.SetHeight(32);
    button3.SetHint(lxT(""));
    button3.SetEnable(1);
    button3.SetVisible(1);
    button3.SetColor(lxT("#000001"));
    button3.SetPopupMenu(NULL);
    button3.EvMouseButtonClick = EVMOUSEBUTTONCLICK & CPWindow3::button3_EvMouseButtonClick;
    button3.SetText(lxT("Open Configuration Dir"));
    CreateChild(&button3);
    // checkbox1
    checkbox1.SetFOwner(this);
    checkbox1.SetClass(lxT("CCheckBox"));
    checkbox1.SetName(lxT("checkbox1"));
    checkbox1.SetTag(0);
    checkbox1.SetX(355);
    checkbox1.SetY(36);
    checkbox1.SetWidth(128);
    checkbox1.SetHeight(32);
    checkbox1.SetHint(lxT(""));
    checkbox1.SetEnable(1);
    checkbox1.SetVisible(1);
    checkbox1.SetPopupMenu(NULL);
    checkbox1.SetText(lxT("DTR/RTS Reset"));
    checkbox1.SetCheck(0);
    CreateChild(&checkbox1);
    /*#Others*/
    // lxrad automatic generated block end, don't edit above!
};