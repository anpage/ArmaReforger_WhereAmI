class PlayerMarker : ScriptedWidgetComponent
{
	protected static SCR_MapUIElement s_SelectedElement;
	protected SCR_GpsUI m_Par;
	protected MapItem m_MapItem;
	protected Widget m_wRoot;
	protected ButtonWidget m_wButton;
	protected ImageWidget m_wImage;
	protected bool m_bVisible = false;
	protected vector position;

	//------------------------------------------------------------------------------
	void SetParent(SCR_GpsUI parent)
	{
		m_Par = parent;
	}

	//------------------------------------------------------------------------------
	void SetVisible(bool visible)
	{
		m_wRoot.SetVisible(visible);
	}

	//------------------------------------------------------------------------------
	void SetOpacity(float val)
	{
		m_wRoot.SetOpacity(val);
	}

	//------------------------------------------------------------------------------
	void SetIconSize(float val)
	{
		FrameSlot.SetSize(m_wRoot, val, val);
	}

	//------------------------------------------------------------------------------
	Widget GetRoot()
	{
		return m_wRoot;
	}

	//------------------------------------------------------------------------------
	vector GetIconSize()
	{
		return FrameSlot.GetSize(m_wButton);
	}

	//------------------------------------------------------------------------------
	override void HandlerAttached(Widget w)
	{
		m_wRoot = w;

		m_wButton = ButtonWidget.Cast(w.FindAnyWidget("Button"));
		m_wImage = ImageWidget.Cast(w.FindAnyWidget("Image"));
	}

	//------------------------------------------------------------------------------
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		return false;
	}

	//------------------------------------------------------------------------------
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		return false;
	}

	// ------------------------------------------------------------------------------
	override bool OnClick(Widget w, int x, int y, int button)
	{
		return false;
	}

	//------------------------------------------------------------------------------
	vector GetPos()
	{
		return position;
	}
	
	//------------------------------------------------------------------------------
	void SetPos(vector v)
	{
		position = v;
	}
};
