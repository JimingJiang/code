<?php
/**
* sign up page
*/
$user = elgg_get_logged_in_user_entity();
$title = "Sign up^_^";
$content = "<br/><div align='center'><h2>";
/*首先判断有没有登录*/
if($user->name)
{
	$guid = $user->guid;
	/*第二步判断今天有没有已经签到，避免重复*/
	$query = "SELECT max(sign_up_time) from Elgg_daily_attendance where guid = {$guid}";
	$link = get_db_link('read');
	//if ($exists = get_data_row($query)) 
	if(($ret = execute_query($query, $link)))
	{

		//注意mysql_fetch_array与mysql_fetch_object()的区别
		$day = mysql_fetch_array($ret);
		$int_time = strtotime($day[0]);
	}

	$now_time = strtotime(date('Y-m-d',time()));//零点时间
	if($now_time < $int_time )
	{
		$content = $content.elgg_echo("今日<u> %s </u>已签到，请勿重复.",array($day[0]));
	}

	else
	{
		$sign_time = date('Y-m-d H:i:s',time());
		$query = "INSERT into Elgg_daily_attendance
					(guid, sign_up_time)
					values ($guid, '$sign_time')";
		insert_data($query);
		$content = $content.elgg_echo('你好，%s，欢迎回来^_^', array($user->name));
	}
}
else
{
	$content = $content.elgg_echo("请先登录...");
}
$content = $content."</h2></div>";
$vars = array( 'content' => $content, );
$body = elgg_view_layout('one_sidebar', $vars);
echo elgg_view_page($title, $body);
