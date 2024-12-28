"""add 'exception' table

Revision ID: 50838e77968d
Revises: 39bbceba090a
Create Date: 2024-12-28 19:23:09.504243

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = '50838e77968d'
down_revision: Union[str, None] = '39bbceba090a'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    # ### commands auto generated by Alembic - please adjust! ###
    op.create_table('app_exceptions',
    sa.Column('id', sa.Integer(), autoincrement=True, nullable=False),
    sa.Column('exception_message', sa.String(), nullable=False),
    sa.Column('recorded_at', sa.DateTime(), nullable=False),
    sa.PrimaryKeyConstraint('id')
    )
    # ### end Alembic commands ###


def downgrade() -> None:
    # ### commands auto generated by Alembic - please adjust! ###
    op.drop_table('app_exceptions')
    # ### end Alembic commands ###
