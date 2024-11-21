"""added_sensor_table

Revision ID: e9798d9f0685
Revises: 1717de7da888
Create Date: 2024-11-21 14:39:02.572314

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa
from sqlalchemy.dialects import postgresql

# revision identifiers, used by Alembic.
revision: str = 'e9798d9f0685'
down_revision: Union[str, None] = '1717de7da888'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    # ### commands auto generated by Alembic - please adjust! ###
    op.drop_table('measurement')
    # ### end Alembic commands ###


def downgrade() -> None:
    # ### commands auto generated by Alembic - please adjust! ###
    op.create_table('measurement',
    sa.Column('id', sa.INTEGER(), autoincrement=True, nullable=False),
    sa.Column('value', sa.DOUBLE_PRECISION(precision=53), autoincrement=False, nullable=False),
    sa.Column('sensor_id', sa.INTEGER(), autoincrement=False, nullable=True),
    sa.Column('recorded_at', postgresql.TIMESTAMP(), autoincrement=False, nullable=False),
    sa.Column('created_at', postgresql.TIMESTAMP(), autoincrement=False, nullable=False),
    sa.Column('test', sa.INTEGER(), autoincrement=False, nullable=True),
    sa.PrimaryKeyConstraint('id', name='measurement_pkey')
    )
    # ### end Alembic commands ###
