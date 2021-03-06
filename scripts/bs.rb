
# desc: trains hiding, stalking and backstabbing for thieves
# requirements: only works for thieves cirlce 70+, pref min. hiding rt
# run: hunting area

#You quickly slip into hiding to prepare to stalk.
#You melt into the background, convinced that your attempt to hide went unobserved.
#It's hard to stalk if you aren't in a position to move around.

@rt_adjust = 0
@arrange_count = 5

if !$args.first
  echo '*** hide on what? usage: .h &lt;critter_name&gt; ***'
  exit
end

def go_wait(label, back_label)
  if label == :wait
    pause 0.5
    goto back_label
  else
    goto label
  end
end

def arrange count
  put "arrange"
  match = { :wait => [/\.\.\.wait|while entangled in a web|you may only type ahead|still stunned/],
            :quit => [/You are still stunned/],
            :arrange => [/You begin to arrange|You continue arranging|complete arranging|You make a mistake/],
            :loot => [/arrange what|cannot be skinned/] }
  result = match_wait match

  case result
    when :wait
      pause 0.5
      arrange count
    when :quit
      put "quit"
    when :arrange
      if count < @arrange_count - 1
        arrange count + 1
      else
        skin
      end
    when :loot
      loot
  end
end

def skin
  if Wield::left_noun != ""
    put "stow left"
  end
  put "skin"
  match = { :wait => [/\.\.\.wait|while entangled in a web|you may only type ahead|still stunned/],
            :quit => [/You are still stunned/],
            :loot => [/Skin what|cannot be skinned|Roundtime/] }
  result = match_wait match

  case result
    when :wait
      pause 0.5
      skin
    when :quit
      put "quit"
    when :loot
      loot
  end
end

def loot
  put "loot"
  match = { :wait => [/\.\.\.wait|while entangled in a web|you may only type ahead|Roundtime|still stunned/],
            :quit => [/You are still stunned/],
            :continue => [/could not find what|You search/] }
  result = match_wait match

  case result
    when :wait
      pause 0.5
      loot
    when :quit
      put "quit"
    when :continue
      goto :start
  end
end

labels_start

label(:start) {
  put "face #{$args.first}"
  match = { :wait_for => ["Face what?"],
            :hide => ["You are already facing", "You turn to face"],
            :retreat => ["You are too closely engaged"],
            :wait => [/\.\.\.wait|facing a dead/] }
  res = match_wait match
  go_wait(res, :start)
}

label(:hide) {
  pause Rt::value
  put "stalk"
  match = { :feint => ["your stalking went unobserved", "slip into hiding to prepare", "melt into the background"],
            :stop_stalk => ["You're already stalking"],
            :hide => ["ruining your hiding"],
            :wait => [/\.\.\.wait/] }
  res = match_wait match
  go_wait(res, :hide)
}

label(:stop_stalk) {
  put "stop stalk"
  pause Rt::value
  goto :feint
}

label(:feint) {
  put "backstab"
  match = { :dead => ["and collapses", "sharp halt", "ceases all movement"],
            :advance => ["would help if you were closer", "aren't close enough"],
            :hide => ["Roundtime", "hidden to backstab"],
            :face => ["You can't backstab that."],
            :wait => [/\.\.\.wait/]}
  res = match_wait match
  go_wait(res, :feint)
}

label(:advance) {
  put "advance"
  put "shiver"
  match = { :hide => ["begin to advance", "You are already", "begin to stealthily advance"],
            :wait => [/\.\.\.wait/]}
  res = match_wait match
  go_wait(res, :advance)
}

label(:dead) {
  arrange 0
}

label(:wait_for) {
  wait_for(/begins to advance you|closes to melee range/)
  goto :start
}

label(:retreat) {
  put "retreat"
  wait
  put "retreat"
  wait
  goto :start
}

labels_end
