class SCR_WhereAmIUI : SCR_MapUIBaseComponent
{
	protected Widget m_widget;

	override void Update()
	{
		if (!m_widget)
			return;

		ChimeraCharacter player = ChimeraCharacter.Cast(SCR_PlayerController.GetLocalControlledEntity());
		if (!player)
		{
			m_widget.RemoveFromHierarchy();
			return;
		}

		vector posPlayer = player.GetOrigin();

		float x, y;
		m_MapEntity.WorldToScreen(posPlayer[0], posPlayer[2], x, y, true);

		x = GetGame().GetWorkspace().DPIUnscale(x);
		y = GetGame().GetWorkspace().DPIUnscale(y);

		FrameSlot.SetPos(m_widget, x, y);
	}

	override void OnMapOpen(MapConfiguration config)
	{
		super.OnMapOpen(config);

		if (m_widget)
		{
			return;
		}

		m_widget = GetGame().GetWorkspace().CreateWidgets("{3513CA0C0C83D2E3}UI/layouts/GPS/PlayerMapIndicator.layout", m_RootWidget);

		ResourceName imageSet = "{C3F217CA9CF060B4}UI/Imagesets/Conflict/ConflictIconsSet.imageset";
		ImageWidget image = ImageWidget.Cast(m_widget.FindAnyWidget("Image"));
		if(image)
		{
			image.LoadImageFromSet(0, imageSet, "OutlineBold");
			image.SetColor(Color.Red);
		}
	}
};
