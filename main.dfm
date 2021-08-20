object Form1: TForm1
  Left = 704
  Top = 195
  Width = 711
  Height = 373
  Caption = 'Thumbgen'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 200
    Top = 24
    Width = 94
    Height = 13
    Caption = 'Szeroko'#347#263' miniatury'
  end
  object Label2: TLabel
    Left = 312
    Top = 24
    Width = 94
    Height = 13
    Caption = 'Wysoko'#347#263' miniatury'
  end
  object SpeedButton1: TSpeedButton
    Left = 272
    Top = 280
    Width = 113
    Height = 30
    Caption = 'Generuj'
    OnClick = SpeedButton1Click
  end
  object Image1: TImage
    Left = 432
    Top = 32
    Width = 249
    Height = 225
    Center = True
    Transparent = True
  end
  object Label3: TLabel
    Left = 432
    Top = 16
    Width = 83
    Height = 13
    Caption = 'Podgl'#261'd miniatury'
  end
  object m: TLabeledEdit
    Left = 32
    Top = 40
    Width = 137
    Height = 21
    EditLabel.Width = 138
    EditLabel.Height = 13
    EditLabel.Caption = 'Nazwa katalogu z miniaturam'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 0
    Text = 'miniatury'
  end
  object szerokosc: TCSpinEdit
    Left = 200
    Top = 40
    Width = 97
    Height = 22
    TabOrder = 1
    Value = 100
  end
  object wysokosc: TCSpinEdit
    Left = 312
    Top = 40
    Width = 97
    Height = 22
    TabOrder = 2
    Value = 100
  end
  object dir: TDirectoryListBox
    Left = 32
    Top = 104
    Width = 377
    Height = 145
    ItemHeight = 16
    TabOrder = 3
  end
  object DriveComboBox1: TDriveComboBox
    Left = 32
    Top = 72
    Width = 377
    Height = 19
    DirList = dir
    TabOrder = 4
  end
  object status: TStatusBar
    Left = 0
    Top = 320
    Width = 703
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object CheckBox1: TCheckBox
    Left = 32
    Top = 256
    Width = 177
    Height = 17
    Caption = 'Zast'#261'p istniej'#261'ce miniatury.'
    TabOrder = 6
  end
  object CheckBox2: TCheckBox
    Left = 32
    Top = 280
    Width = 185
    Height = 17
    Caption = 'Popraw nazwy - usu'#324' spacje.'
    TabOrder = 7
  end
end
