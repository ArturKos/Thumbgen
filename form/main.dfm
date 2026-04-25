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
  object widthLabel: TLabel
    Left = 200
    Top = 24
    Width = 94
    Height = 13
    Caption = 'Thumbnail width'
  end
  object heightLabel: TLabel
    Left = 312
    Top = 24
    Width = 94
    Height = 13
    Caption = 'Thumbnail height'
  end
  object generateButton: TSpeedButton
    Left = 272
    Top = 280
    Width = 113
    Height = 30
    Caption = 'Generate'
    OnClick = generateButtonClick
  end
  object previewImage: TImage
    Left = 432
    Top = 32
    Width = 249
    Height = 225
    Center = True
    Transparent = True
  end
  object previewLabel: TLabel
    Left = 432
    Top = 16
    Width = 83
    Height = 13
    Caption = 'Thumbnail preview'
  end
  object outputFolderName: TLabeledEdit
    Left = 32
    Top = 40
    Width = 137
    Height = 21
    EditLabel.Width = 138
    EditLabel.Height = 13
    EditLabel.Caption = 'Output folder name'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 0
    Text = 'thumbnails'
  end
  object thumbnailWidth: TCSpinEdit
    Left = 200
    Top = 40
    Width = 97
    Height = 22
    TabOrder = 1
    Value = 100
  end
  object thumbnailHeight: TCSpinEdit
    Left = 312
    Top = 40
    Width = 97
    Height = 22
    TabOrder = 2
    Value = 100
  end
  object directoryList: TDirectoryListBox
    Left = 32
    Top = 104
    Width = 377
    Height = 145
    ItemHeight = 16
    TabOrder = 3
  end
  object driveCombo: TDriveComboBox
    Left = 32
    Top = 72
    Width = 377
    Height = 19
    DirList = directoryList
    TabOrder = 4
  end
  object statusBar: TStatusBar
    Left = 0
    Top = 320
    Width = 703
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object replaceExistingCheckBox: TCheckBox
    Left = 32
    Top = 256
    Width = 177
    Height = 17
    Caption = 'Replace existing thumbnails'
    TabOrder = 6
  end
  object fixNamesCheckBox: TCheckBox
    Left = 32
    Top = 280
    Width = 185
    Height = 17
    Caption = 'Fix names - remove spaces'
    TabOrder = 7
  end
end
