from mblock import event
# initialize variables


@event.keypressed('d')
def on_keypressed():
  if not sprite.touching('edge'):
    v = sprite.get_variable('☁ $')
    sprite.set_variable('☁ $', v + 4)

  if sprite.touching('edge'):
    v = sprite.get_variable('☁ $')
    sprite.set_variable('☁ $', v + -4)

  sprite.x = sprite.x + 7
  sprite.forward(14)
  sprite.right(14)
  sprite.change_effect_by('color', 25)
  sprite.change_effect_by('whirl', 25)
  sprite.change_effect_by('whirl', -25)
  sprite.clone('_myself_')
  # not supported yet

@event.keypressed('a')
def on_keypressed1():
  if not sprite.touching('edge'):
    v = sprite.get_variable('☁ $')
    sprite.set_variable('☁ $', v + 4)

  if sprite.touching('edge'):
    v = sprite.get_variable('☁ $')
    sprite.set_variable('☁ $', v + -4)

  sprite.x = sprite.x + -7
  sprite.forward(14)
  sprite.right(14)
  sprite.change_effect_by('color', 25)
  sprite.change_effect_by('whirl', 25)
  sprite.change_effect_by('whirl', -25)
  sprite.clone('_myself_')
  # not supported yet

@event.keypressed('w')
def on_keypressed2():
  v = sprite.get_variable('☁ $')
  sprite.set_variable('☁ $', v + 4)
  if not sprite.touching('edge'):
    v = sprite.get_variable('☁ $')
    sprite.set_variable('☁ $', v + 4)

  if sprite.touching('edge'):
    v = sprite.get_variable('☁ $')
    sprite.set_variable('☁ $', v + -4)

  sprite.y = sprite.y + 7
  sprite.forward(14)
  sprite.right(14)
  sprite.change_effect_by('color', 25)
  sprite.change_effect_by('whirl', 25)
  sprite.change_effect_by('whirl', -25)
  sprite.clone('_myself_')
  # not supported yet

@event.greenflag
def on_greenflag():
  sprite.set_variable('☁ $', 0)
  while True:
    if sprite.is_mousedown:
      sprite.goto('random')
      sprite.goto('mouse')
      sprite.forward(14)
      sprite.right(14)
      sprite.change_effect_by('color', 25)
      sprite.change_effect_by('whirl', 25)
      sprite.change_effect_by('whirl', -25)
      sprite.clone('_myself_')
      # not supported yet

    if not sprite.touching('edge'):
      v = sprite.get_variable('☁ $')
      sprite.set_variable('☁ $', v + 4)

    if sprite.touching('edge'):
      v = sprite.get_variable('☁ $')
      sprite.set_variable('☁ $', v + -4)

@event.keypressed('s')
def on_keypressed3():
  if not sprite.touching('edge'):
    v = sprite.get_variable('☁ $')
    sprite.set_variable('☁ $', v + 4)

  if sprite.touching('edge'):
    v = sprite.get_variable('☁ $')
    sprite.set_variable('☁ $', v + -4)

  sprite.y = sprite.y + 7
  sprite.forward(14)
  sprite.right(14)
  sprite.change_effect_by('color', 25)
  sprite.change_effect_by('whirl', 25)
  sprite.change_effect_by('whirl', -25)
  sprite.clone('_myself_')
  # not supported yet

@event.keypressed('m')
def on_keypressed4():
  sprite.play_until_done('Minecraft Otherside piano')
  v = sprite.get_variable('☁ $')
  sprite.set_variable('☁ $', v + 4)
